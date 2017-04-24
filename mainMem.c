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
memLoc *newMemLoc(int i,char opType, int addr, int blksize, int cachesets, int N)
{
	memLoc *mL = malloc(sizeof(memLoc));
	mL->opNum = i;
	mL->operation = opType;
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
	fprintf(stdout, "\t%d\t\t   %d\t   %d\t %d -- %d\t   %s",
	m->address, m->mmblk, m->cmset, m->cmblk_bottom, m->cmblk_top, m->hit_miss);
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
char getMMOp(memLoc *m)
{
	return m->operation;
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

double DectoBin(int address)
{
	long remainder;
	long binary = 0;
	long b = 1;
	address = (long) address;
	while(address!=0)
	{
		remainder = address%2;
		address = address/2;
		binary = binary + (remainder *b);
		b*=10;
	}
	return binary;
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
int i = 0;
int isNegative = 0;

/* Handle 0 explicitely, otherwise empty string is printed for 0 */
if (num == 0)
{
str[i++] = '0';
str[i] = '\0';
return str;
}

// In standard itoa(), negative numbers are handled only with 
// base 10. Otherwise numbers are considered unsigned.
if (num < 0 && base == 10)
{
isNegative = 1;
num = -num;
}

// Process individual digits
while (num != 0)
{
int rem = num % base;
str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
num = num/base;
}

// If number is negative, append '-'
if (isNegative)
str[i++] = '-';

str[i] = '\0'; // Append string terminator

// Reverse the string
reverse(str, i);

return str;
}