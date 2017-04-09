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
/////////////////End Main Mem Stuff/////////////////////////



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