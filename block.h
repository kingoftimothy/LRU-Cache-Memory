#ifndef _BLOCK_H_
#define _BLOCK_H_

/* 
 * Represents a memory system cache block.  Stores the meta data
 * used to identify each unique block and its current state.
 */
struct block{
  unsigned long long int tag;
  int lru;
  int valid;
};


#endif
