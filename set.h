#ifndef _SET_H_
#define _SET_H_

#include <stdlib.h>
#include "block.h"

/* 
 * Represents a set in a memory system cache. Aset is an array of
 * cache blocks where each cache block stores meta data about the part
 * of memory it stores.
 */
struct set{
  struct block *blocks;
  int associativity;
};

/* 
 * Returns a pointer to a dynamically allocated set with the specified
 * number of blocks allocated and initialized.
 */
struct set *initializeSet(int associativity);

/* 
 * Frees all memory dynamically allocated to store set data structure 
 */
void freeSet(struct set* set);


/* 
 * Adds the access of specified tag to the set.  Returns 1 if
 * was a hit.  Returns 0 if a miss with no eviction, -1 if a 
 * miss that caused an eviction.
 */
int addSetAccess(struct set*s, unsigned long long int tag);


/*
 * Checks each Block's LRU to determine the block with the
 * least Recently Accessed number (biggest LRU value).
 * Returns the index with this LRU. Return -1 if not found.
 */
int leastRecentlyAccessedBlockIndex(struct set* set);

/*
 * Updates the LRU of each valid Block in the set. Changes the
 * most recently accessed block to a LRU value of 0. Increases
 * every other block's LRU by 1.
 */
void changeLRUOfBlocks(struct set* set, int indexOfMostRecent);

#endif
