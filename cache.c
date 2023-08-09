#include "cache.h"
#include <stdio.h>

/* 
 * Returns a pointer to a dynamically allocated cache with the specified
 * associativity and using the number of specified set index bits and block 
 * offset bits.
 */
struct cache *initializeCache(int setIndexBits, int associativity,
			     int blockOffsetBits) {
  struct cache *allocatedCache = (struct cache*) malloc(sizeof(struct cache));
  allocatedCache->sets = (struct set**) malloc((1 << setIndexBits) * sizeof(struct set*));
  
  // hit, miss, eviction statistics
  allocatedCache->hit_count = 0;
  allocatedCache->miss_count = 0;
  allocatedCache->eviction_count = 0;
  
  // initialize sets in the cache
  for (int i = 0; i < (1 << setIndexBits); i++) {
    allocatedCache->sets[i] = initializeSet(associativity);
  }
  
  // set index, associativity, and block offset bits from command line
  allocatedCache->setIndexBits = setIndexBits;
  allocatedCache->associativity = associativity;
  allocatedCache->blockOffsetBits = blockOffsetBits;
  
  return allocatedCache;
}

/* 
 * Frees all memory dynamically allocated to store cache data structure 
 */
void freeCache(struct cache *cache) {
  // goes through each set in the cache and frees memory individually
  for (int i = 0; i < (1 << (cache->setIndexBits)); i++) {
    free(cache->sets[i]);
  }
  
  // frees the memory for entire struct cache
  free(cache);
}


/* 
 * Adds the access of specified address to the cache.  
 */
void addCacheAccess(struct cache *cache, unsigned long long int address) {
  if (cache != NULL) {
    // bit masks for tag, set index, and block offset from address of word
    int setMask = (1 << cache->setIndexBits) - 1;
  
    // set index and tag
    int set = (address >> cache->blockOffsetBits) & setMask;
    unsigned long long int tag = (address >> (cache->blockOffsetBits + cache->setIndexBits));
  
    // access the set and records miss, hit, or eviction
    int missHitEviction = addSetAccess(cache->sets[set], tag);
  
    // if hit
    if (missHitEviction == 1) {
      cache->hit_count++;
    } 
    
    // if miss with eviction
    else if (missHitEviction == -1) {
      cache->miss_count++;
      cache->eviction_count++;
    }
    
    // if miss without eviction 
    else {
      cache->miss_count++;
    }
  }
}
