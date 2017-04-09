#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include "mainMem.h"


/////////////////Cache Stuff/////////////////////////////
cache *newCache(int aLines,int size, int linesize, int n, char r)
{ 
	cache *c = malloc(sizeof(cache));
	c->size = size;
	c->blockSize = linesize;
	c->cacheBlocks = size / linesize;
	c->assoc = n;
	c->cacheSets = c->cacheBlocks / c->assoc;
	c->replacement = r;
	c->offbits = numberofbits(linesize);
	c->indexbits = numberofbits(c->cacheSets);
	c->tagbits = aLines - (c->offbits + c->indexbits);
	c->totalCache = size + (c->tagbits+2) * (c->cacheBlocks/8);
	return c;
}

int offBits(cache *c)
{
	return c->offbits;
}

int indexBits(cache *c)
{
	return c->indexbits;
}

int tagBits(cache *c)
{
	return c->tagbits;
}

int totCacheSize(cache *c)
{
	return c->totalCache;
}
//////////////////////////End Cache Stuff////////////////////////////////////