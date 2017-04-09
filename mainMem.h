#ifndef MAINMEM_INCLUDED_
#define MAINMEM_INCLUDED_

typedef struct mainMem
{
	int size;
	int lines;
	
}mainMem;

extern mainMem *newMem(int size);
extern int addressLines(mainMem *m);

extern int numberofbits(int num);

#endif