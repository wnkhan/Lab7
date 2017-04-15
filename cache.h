#ifndef CACHE_INCLUDED_
#define CACHE_INCLUDED_

typedef struct cache
{
	int size;
	int blockSize;
	int cacheBlocks;
	int assoc;
	char replacement;
	int cacheSets;
	int offbits;
	int indexbits;
	int tagbits;
	int totalCache;
	
}cache;

typedef struct cacheBlock
{
	int data;
	int dirty;
	int valid;
	char *tag;
}cacheBlock;

extern cache *newCache(int aLines, int size, int linesize, int assoc, char replacement);
extern int offBits(cache *c);
extern int indexBits(cache *c);
extern int tagBits(cache *c);
extern int totCacheSize(cache *c);
extern int CacheBlockSize(cache *c);
extern int CacheSets(cache *c);
extern int Associativity(cache *c);

extern cacheBlock *newCBlock(int mmblk);
extern cacheBlock *getCBlock(cacheBlock *cb);
extern void displayC(FILE *fp, void *v);
extern int getData(cacheBlock *cb);


#endif