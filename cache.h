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

extern cache *newCache(int aLines, int size, int linesize, int assoc, char replacement);
extern int offBits(cache *c);
extern int indexBits(cache *c);
extern int tagBits(cache *c);
extern int totCacheSize(cache *c);


#endif