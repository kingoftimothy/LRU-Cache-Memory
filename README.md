# CS237 Cache Lab

 * [Lab Handout](http://cs.williams.edu/~cs237/labs/lab05/index.html)
 * [Useful Links](http://cs.williams.edu/~cs237/links.html)
 * [Course Homepage](http://cs.williams.edu/~cs237/index.html) with TA and office hour schedule

## Lab Overview

 * Before running the checker, compile your code:
    ```
    $ make
    ```

 * Check the correctness of your simulator for part A:
    ```
    $ ./test-csim
    ```

 * Check the correctness and performance of your transpose function in part B (extra credit):
    ```
    $ ./test-trans -M 32 -N 32
    $ ./test-trans -M 64 -N 64
    $ ./test-trans -M 61 -N 67    
    ```

## Lab Files:

### You will modifying and handing in several C files:
 * `csim.c`: Your cache simulator
 * `cache.[ch]`: Your cache simulator
 * `set.[ch]`: Your cache simulator
 * `block.h`: Your cache simulator 
 * `trans.c`: Your transpose function (extra credit)

### Tools for evaluating your simulator 
 * `Makefile`     Builds the simulator and tools
 * `README.md`    This file
 * `cachelab.c`   Required helper functions
 * `cachelab.h`   Required header file
 * `csim-ref*`    The executable reference cache simulator
 * `test-csim*`   Tests your cache simulator against the reference
 * `test-trans.c` Tests your transpose function (extra credit)
 * `tracegen.c`   Helper program used by test-trans (extra credit)
 * `traces/`      Trace files used by test-csim.c

## Insert your honor code statement below:
Timothy Kim and Michelle Wang
