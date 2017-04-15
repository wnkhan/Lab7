#ifndef MAINMEM_INCLUDED_
#define MAINMEM_INCLUDED_
//////////////Main Mem////////////////
typedef struct mainMem
{
	int size;
	int lines;
	
}mainMem;

extern mainMem *newMem(int size);
extern int addressLines(mainMem *m);

/////////////////////////////////////

///////////Memory locations////////

typedef struct memLoc
{
	int address;
	int mmblk;
	int cmset;
	int cmblk_top;
	int cmblk_bottom;
	char *hit_miss;
}memLoc;

extern memLoc *newMemLoc(int addr, int blksize, int cachesets, int N);
extern memLoc *getMemLoc(memLoc *m);
extern void displayMem(FILE *, void *);
extern int getMMBlk(memLoc *m);
extern int getCSet(memLoc *m);
extern int getAddress(memLoc *m);

///////////////////////////////////

////////////Helper functions///////
extern int numberofbits(int num);
////////////////////////////////////
#endif