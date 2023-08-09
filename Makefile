#
# Student makefile for Cache Lab
# Note: requires a 64-bit x86-64 system 
#
CC = gcc
CFLAGS = -g -Wall -Werror -std=c99 -m64
ASFLAGS = -fsanitize=address

all: csim test-trans trans.o tracegen ascsim

csim: csim.c cachelab.c cachelab.h cache.c cache.h set.c set.h block.h
	$(CC) $(CFLAGS) -o csim csim.c cachelab.c cache.c set.c -lm 

test-trans: test-trans.c trans.o cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o test-trans test-trans.c cachelab.c trans.o 

ascsim: csim.c
	$(CC) $(CFLAG) $(ASFLAGS) -o ascsim csim.c cachelab.c cache.c set.c -lm

tracegen: tracegen.c trans.o cachelab.c
	$(CC) $(CFLAGS) -O0 -o tracegen tracegen.c trans.o cachelab.c

trans.o: trans.c
	$(CC) $(CFLAGS) -O0 -c trans.c

#
# Clean the src dirctory
#
clean:
	rm -rf *.o csim test-trans tracegen 
	rm -f .csim_results .marker
