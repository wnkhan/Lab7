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
memLoc *newMemLoc(int i, int addr, int blksize, int cachesets, int N)
{
	memLoc *mL = malloc(sizeof(memLoc));
	mL->opNum = i;
	mL->address = addr;
	mL->mmblk = addr/blksize;
	mL->cmset = mL->mmblk % cachesets;
	mL->cmblk_top = (mL->cmset * N) + (N -1);
	mL->cmblk_bottom = (mL->cmblk_top - N) + 1;
	mL->hit_miss = "miss";
}

memLoc *getMemLoc(memLoc *m)
{
	return m;
}

void displayMem(FILE *fp, void *v)
{
	memLoc *m = getMemLoc(v);
	fprintf(stdout, "%d \t%d\t\t   %d\t   %d\t %d -- %d\t   %s",
	m->opNum, m->address, m->mmblk, m->cmset, m->cmblk_bottom, m->cmblk_top, m->hit_miss);
}

int getMMBlk(memLoc *m)
{
	return m->mmblk;
}

int getCSet(memLoc *m)
{
	return m->cmset;
}

int getAddress(memLoc *m)
{
	return m->address;
}

int getOpNum(memLoc *m)
{
	return m->opNum;
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