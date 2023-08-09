#include "set.h"

/* 
 * Returns a pointer to a dynamically allocated set with the specified
 * number of blocks allocated and initialized.
 */
struct set *initializeSet(int associativity) {
  // allocate memory for set
  struct set *allocatedSet = (struct set*) malloc(sizeof(struct set));
  
  // initialize set variables
  allocatedSet->associativity = associativity;
  allocatedSet->blocks = (struct block*) malloc(associativity * sizeof(struct block));
  
  // initialize all valid bits of blocks to 0
  for (int i = 0; i < associativity; i++) {
    allocatedSet->blocks[i].valid = 0;
  }
  
  return allocatedSet;
}

/* 
 * Frees all memory dynamically allocated to store set data structure 
 */
void freeSet(struct set* set) {
  // frees memory for each block in the set
  free(set->blocks);
  
  // frees the memory for entire set struct
  free(set);
}


/* 
 * Adds the access of specified tag to the set.  Returns 1 if
 * was a hit.  Returns 0 if a miss with no eviction, -1 if a 
 * miss that caused an eviction.
 */
int addSetAccess(struct set*s, unsigned long long int tag) {
  // if pointer is NULL, treat as a miss without eviction
  if (s == NULL) {
    return 0;
  }
  
  // an open/invalid block to write to
  int nextAvailableBlockToWrite = -1;
  
  // loop through each block in set and check for a hit
  for (int i = 0;  i < s->associativity; i++) {
    
    // hit case
    if (s->blocks[i].valid && s->blocks[i].tag == tag) {
      // update LRU of every block
      changeLRUOfBlocks(s, i);
      
      return 1;
    } 
    
    // miss case
    else if (!(s->blocks[i].valid)) {
        // index for next available block to write to
        // for misses with no eviction
        nextAvailableBlockToWrite = i;
    }
  }
  
  // miss cases: check for eviction
  
  // miss with eviction case
  if (nextAvailableBlockToWrite < 0) {
    // find and evict/write to block with largest LRU
    int leastAccessed = leastRecentlyAccessedBlockIndex(s);
    s->blocks[leastAccessed].tag = tag;
    
    // update LRU of every block
    changeLRUOfBlocks(s, leastAccessed);
    
    return -1;
  }
  
  // miss with no eviction case
  // write to next available block
  s->blocks[nextAvailableBlockToWrite].tag = tag;
  s->blocks[nextAvailableBlockToWrite].valid = 1;
  s->blocks[nextAvailableBlockToWrite].lru = s->associativity - 1;
  changeLRUOfBlocks(s, nextAvailableBlockToWrite);  
  
  return 0;
}


/*
 * Checks each Block's LRU to determine the block with the
 * least Recently Accessed number (biggest LRU value).
 * Returns the index with this LRU. Return -1 if not found.
 */
int leastRecentlyAccessedBlockIndex(struct set* set) {
  // loop through all blocks in set and find block with max LRU
  for (int i = 0; i < set->associativity; i++) {
    if (set->blocks[i].lru == (set->associativity - 1)) {
      return i;
    }
  }
  
  return 0;
}


/*
 * Updates the LRU of each valid Block in the set. Changes the
 * most recently accessed block to a LRU value of 0. Increases
 * every other block's LRU by 1.
 */
void changeLRUOfBlocks(struct set* set, int accessIndex) {
  // update LRU of each block with a lower LRU than block with pecific index
  for (int i = 0; i < set->associativity; i++) {
    if (set->blocks[i].lru < (set->blocks[accessIndex].lru) &&
    set->blocks[i].valid) {
      set->blocks[i].lru++;
    }
  }
  
  //  update LRU of most recently access block to 0
  set->blocks[accessIndex].lru = 0;
}
