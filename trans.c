/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
  // 11 int variables defined
  
  // variable to loop through rows and columns
  // rows and columns set to each combination of submatrixes
  int column;
  int row;

  // variables used to loop through each of the submatrixes
  int i = 0;
  int j = 0;
  
  // variable to hold the diagonal indexes of the matrix
  int d = 0;
  
  // variable to temporarily store the value of the miss case
  int valueOfMiss32;
  int valueOfMiss64;
  int valueOfMiss67;
  
  // constant block size for adjustments
  int blockSizeOf32 = 8;
  int blockSizeOf64 = 4;
  int blockSizeOf67 = 16;

  // case for M=32 and N=32 matrix
  if(M == 32) {

    // loops through submatrices of the 32x32 matrix with the block size of 8
    for(row = 0; row < N; row += blockSizeOf32) {
      
      for(column = 0; column < M; column += blockSizeOf32) {
	// loops through the submatrix which is an 8x8 matrix
	for(i = row; i < row + blockSizeOf32; i++) {
	  
	  for(j = column; j < column + blockSizeOf32; j++) {
	    // checks if the value is a diagonal value
	    if(i == j) {
	      // d is a temporary variable to hold the diagonal index
	      d = i;
	      // when we transpose a even numbered matrix, the elements 
	      // along the diagonal of the matrix remain the same.
	      // temporarily store value to resolve the cache miss
	      valueOfMiss32 = A[i][j];
	    }
	    
	    else {
	      // when the value is not a diagonal value, the elements
	      // at [row, col] and [col, row] are swapped (transposed)
	      B[j][i] = A[i][j];
	    }
	  }
	  // when value is at a diagonal index of the matrix, place the 
	  // temporarily stored "miss" value on the appropriate diagonal
	  // index of the output matrix B
	  if(row == column){
	    B[d][d] = valueOfMiss32;
	  }
	}
      }
    }
  }

  // case for M=64 and N=64 matrix
  else if(M == 64) {
    // loops through submatrices of the 64x64 matrix with the block size of 8
    for(row = 0; row < M; row += blockSizeOf64) {
      
      for(column = 0; column < M; column += blockSizeOf64) {
        // loops through the submatrix which is an 8x8 matrix
        for(i = row; i < row + blockSizeOf64; i++) {

          for(j = column; j < column + blockSizeOf64; j++) {
            // checks if the value is a diagonal value
            if(i == j) {
              // d is a temporary variable to hold the diagonal index
              d = i;
              // when we transpose a even numbered matrix, the elements 
              // along the diagonal of the matrix remain the same.
              // temporarily store value to resolve the cache miss
              valueOfMiss64 = A[i][j];
            }
            
            else {
	      // when the value is not a diagonal value, the elements
	      // at [row, col] and [col, row] are swapped (transposed)
              B[j][i] = A[i][j];
            }
          }
	  // when value is at a diagonal index of the matrix, place the 
	  // temporarily stored "miss" value on the appropriate diagonal
	  // index of the output matrix B
          if(row == column) {
            B[d][d] = valueOfMiss64;
          }
        }
      }
    }
  }

  // case for M=61 and N=67 matrix
  // same logic as 64x64 and 32x32 case except the dimesnions are different
  // so the bounds have to checked in the inner submatrices loops to avoid
  // segmentation fault
  else {
   // loops through submatrices of the 61x67 matrix with the block size of 16
   for(row = 0; row < N; row += blockSizeOf67) {
   
     for(column = 0; column < M; column += blockSizeOf67) {
       // loops through the submatrix which is an 16x16 matrix.
       // checks in case for segementaion fault when i goes over because
       // 16 doesnt divide evenly into 67 and 61
       for(i = row;  (i < row + blockSizeOf67) && (i < 67); i++) {
         
         for(j = column; (j < column + blockSizeOf67) && (j < 61); j++) {
           // checks if the value is a diagonal value
           // checks for segmentation fault
           if(i == j) {
             // d is a temporary variable to hold the diagonal index
             d = i;
             // when we transpose a even numbered matrix, the elements 
             // along the diagonal of the matrix remain the same.
             // temporarily store value to resolve the cache miss
             valueOfMiss67 = A[i][j];
           }
	   
          else {
            // when the value is not a diagonal value, the elements
            // at [row, col] and [col, row] are swapped (transposed)
            B[j][i] = A[i][j];  
          }
        }
          // when value is at a diagonal index of the matrix, place the 
          // temporarily stored "miss" value on the appropriate diagonal
          // index of the output matrix B
          if(row == column) {
            B[d][d] = valueOfMiss67;
          }
        }
      }
    }
  }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
