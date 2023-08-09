#include "cachelab.h"
#include "cache.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LENGTH 60
#define MEM_ADDRESS_SIZE 64

/* Read given trace file line by line and access the cache
 * idenfies type of memory access as either L, S, or M
 * L: load (requires 1 memory access)
 * S: store (requires 1 memory access)
 * M: modify (requires 2 memory accesses) 
 */
void readTrace(char* fileName, struct cache * cache) {
  FILE *fp;
  char str[LENGTH];  

  fp = fopen(fileName, "r");

  if(fp == NULL) {
    perror("Error opening file");
    exit(1);
  }

  // read trace file
  while(fgets(str, LENGTH, fp) != NULL) {
    char instructLoad;
    char dataLoad;
    unsigned long long int address;
    char size;

    sscanf(str, "%c%c %llx,%hhd" , &instructLoad, &dataLoad, &address, &size);

    switch(dataLoad) {

      // data modify                                                                        
      case 'M':
        addCacheAccess(cache, address);
        addCacheAccess(cache, address);
        break;

      // data load                                                                          
      case 'L':
        addCacheAccess(cache, address);
        break;

      // data store                                                                         
      case 'S':
        addCacheAccess(cache, address);
        break;

      default:
        break;
    }
  }
  
  fclose(fp);
}

/*
 * A cache simulator that takes a valgrind memory trace as input, 
 * simulates the hit/miss behavior of a cache memory on this trace, 
 * and outputs the total number of hits, misses, and evictions. 
 */       
int main(int argc, char **argv) {
    //argc: num of arguments passed
    //argv: array of arguments
  
    // initialize variables
    char *fileName;
    struct cache * cache;
    int c;
    char *cvalue = NULL;
    int setBits = 0;
    int assoc = 0;
    int blockBits = 0;
    
    // takes in and parses command line arguments
    while((c = getopt(argc,argv,"hvs:E:b:t:")) != -1) {
    
      switch(c) {

	// Number of set index bits (S = 2^s is the number of sets) 
	case 's':
	  cvalue = optarg;
	  setBits = atoi(cvalue);
	  break;

	// Associativity (number of lines per set) 
	case 'E':
	  cvalue = optarg;
	  assoc = atoi(cvalue);
	  break;

	// Number of block bits (B = 2^b is the block size) 
	case 'b':
	  cvalue = optarg;
	  blockBits = atoi(cvalue);
	  break;

	// Name of the valgrind trace to replay 
	case 't':
	  cvalue = optarg;
	  fileName = cvalue;
	  break;

	// Error parsing
	default:
	  printf("Unable to parse.");
      }
    }

    // Check that necessary command line args were specified
    if (setBits == 0 || assoc == 0 || blockBits == 0 || fileName == NULL) {
      printf("Missing command line arguments.\n");
      exit(1);
    }
    
    // initialize cache
    cache = initializeCache(setBits, assoc, blockBits);

    // read trace file
    readTrace(fileName, cache);
    
    // print the total number of hits, misses, and evictions
    printSummary(cache->hit_count, cache->miss_count, cache->eviction_count);

    // free allocated memory for cache
    freeCache(cache);
    
    return 0;
}
