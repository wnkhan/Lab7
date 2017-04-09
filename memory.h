#ifndef MEMORY_INCLUDED_
#define MEMORY_INCLUDED_

typedef struct mainMem
{
	int size;
	int lines;
	
}mainMem;

typedef struct cache
{
	int size;
	int blockSize;
	// int cacheBlocks;
	int assoc;
	// char replacement;
	// int cacheSets;
	// int offbits;
	// int indexbits;
	// int tagbits;
	// int totalCache;
	
}cache;

typedef struct cacheblk
{
	int blknum;
	int dbit;
	int vbit;
	int tag;
	int mmblk;

}cacheblk;

extern mainMem *newMem(int size);
extern int addressLines(mainMem *m);

extern cache *newCache(int size, int linesize, int assoc, char replacement);
extern int offBits(cache *c);
extern int indexBits(cache *c);
extern int tagBits(cache *c);
extern int totCacheSize(cache *c);

extern int numberofbits(int num);

#endif