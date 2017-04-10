#include <stdio.h>
#include <stdlib.h>
#include "mainMem.h"

////////////////////Main Mem Stuff//////////////////////////

mainMem *newMem(int size)
{	
	mainMem *m = malloc(sizeof(mainMem));
	m->size = size;
	m->lines = numberofbits(size);
	return m;
}

int addressLines(mainMem *m)
{
	return m->lines;
}
//////////////////////////////////////////////////////////

///////////////////Mem Locations/////////////////////////
memLoc *newMemLoc(int addr, int blksize, int cachesets, int N)
{
	memLoc *mL = malloc(sizeof(memLoc));
	mL->address = addr;
	mL->mmblk = addr/blksize;
	mL->cmset = mL->mmblk % cachesets;
	mL->cmblk = mL->cmset * N;
	mL->hit_miss = "in progress";
}

memLoc *getMemLoc(memLoc *m)
{
	return m;
}

void displayMem(FILE *fp, void *v)
{
	memLoc *m = getMemLoc(v);
	fprintf(stdout, "\t%d\t\t   %d\t   %d\t   %d\t   %s", m->address, m->mmblk, m->cmset, m->cmblk, m->hit_miss);
}



/////////////////////////////////////////////////////////

///////////////////////Helper functions///////////////////////////////////////////////////////
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