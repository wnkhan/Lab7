#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

mainMem *newMem(int size)
{	
	mainMem *m = malloc(sizeof(mainMem));
	m->size = size;
	m->lines = numberofbits(size);
	return m;
}

cache *newCache(int size, int linesize, int n, char r)
{ 
	cache *c = malloc(sizeof(cache));
	c->size = size;
	c->blockSize = linesize;
	// c->cacheBlocks = size / linesize;
	c->assoc = n;
	// c->cacheSets = c->cacheBlocks / c->assoc;
	// c->replacement = r;
	// c->offbits = numberofbits(linesize);
	// c->indexbits = numberofbits(c->cacheSets);
	// c->tagbits = aLines - (c->offbits + c->indexbits);
	// c->totalCache = size + (c->tagbits+2) * (c->cacheBlocks/8);
	return c;
}

int addressLines(mainMem *m)
{
	return m->lines;
}

// int offBits(cache *c)
// {
// 	return c->offbits;
// }

// int indexBits(cache *c)
// {
// 	return c->indexbits;
// }

// int tagBits(cache *c)
// {
// 	return c->tagbits;
// }

// int totCacheSize(cache *c)
// {
// 	return c->totalCache;
// }

//Shifts through all the bits in a given number to determine max bits needed for decmial version.
int numberofbits(int num){

	int count = 0;
	
	while (num != 0)
	{
		count += 1;
		num = (num >> 1);
	}
		count = count -1;
		return count;
}