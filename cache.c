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
cacheBlock *newCBlock(char oper, int mmblk, int age, int valid)
{
	cacheBlock *cb = malloc(sizeof(cacheBlock));
	if (oper == 'R')
	{
		cb->dirty = 0;
	}
	else
	{
		cb->dirty = 1;
	}
	cb->blk_num = 0;
	cb->age = age;
	cb->data = mmblk;
	cb->valid = valid;
	cb->itag = 0;
}

cacheBlock *getCBlock(cacheBlock *cb)
{
	return cb;
}

void displayC(FILE *fp, void *v)
{
	cacheBlock *cb = getCBlock(v);
	if (cb->data == -1)
	{
		fprintf(fp, "\t%d \t%d \t%d \t%.0f \tmmblk # xxx \t", cb->blk_num, cb->dirty, cb->valid, cb->itag);
	}
	else
	{
		fprintf(fp, "\t%d \t%d \t%d \t%.0f \tmmblk # %d \t", cb->blk_num, cb->dirty, cb->valid, cb->itag, cb->data);
	}
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

void setCBNum(cacheBlock *cb, int number)
{
	cb->blk_num = number;
}

void setTag(cacheBlock *cb, int address, int tagSize, int totalSize)
{
	double tempTag = DectoBin(address);

	int i;
	for (i = 0; i < totalSize-tagSize; ++i)
	{
		tempTag /= 10;
	}
	cb->itag = tempTag;
	cb->ctag = itoa(cb->itag, cb->ctag, 2);
}