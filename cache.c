#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int CacheBlockSize(cache *c)
{
	return c->blockSize;
}

int CacheSets(cache *c)
{
	return c->cacheSets;
}
int Associativity(cache *c)
{
	return c->assoc;
}

//////////////////////////End Cache Stuff////////////////////////////////////

/////////////////cacheBlock stuff//////////////////////////
cacheBlock *newCBlock(int mmblk, int age)
{
	cacheBlock *cb = malloc(sizeof(cacheBlock));
	cb->age = age;
	cb->data = mmblk;
	cb->dirty = 0;
	cb->valid = 0;
	cb->tag = "in progress";
}

cacheBlock *getCBlock(cacheBlock *cb)
{
	return cb;
}

void displayC(FILE *fp, void *v)
{
	cacheBlock *cb = getCBlock(v);
	fprintf(fp, "\t%d \t%d \t%s mmblk # %d \tage = %d", cb->dirty, cb->valid, cb->tag, cb->data, cb->age);
}

int getData(cacheBlock *cb)
{
	return cb->data;
}

int getAge(cacheBlock *cb)
{
	return cb->age;
}

void updateAge(cacheBlock *cb, int age)
{
	cb->age = age;
}