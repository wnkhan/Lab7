//Lab7 -- ECE487
#include <stdio.h>
#include <stdlib.h>
#include "mainMem.h"
#include "cache.h"
#include "queue.h"
#include "sll.h"


int main()
{
	int mainbytes, cachebytes, blocksize, N;
	char replacement, input[20];


	printf("Enter the size of the main memory in bytes:");
	scanf("%d", &mainbytes);    //Main memory size is stored in mainbytes.
	//printf("%d\n", mainbytes);

	printf("Enter the size of the cache in bytes:");
	scanf("%d", &cachebytes);   //Cache size is stored in cachebytes.
	//printf("%d\n", cachebytes);

	printf("Enter the cache block/line size:");
	scanf("%d", &blocksize);    //Block size is store in blocksize.
	//printf("%d\n", blocksize);
	
	printf("Enter the degree of set-associativity(input n for an n-way set-associative mapping):");
	scanf("%d", &N);            //N for associativity
	//printf("%d\n", N);

	printf("Enter the replacement policy (L=LRU, F=FIFO):");
	scanf(" %c", &replacement);  //Replacement holds the replacement policy for the cache.
	
	printf("Enter the name of the input file containing the list of memory references generated\n");
	printf("by the CPU: ");
	scanf("%s", input);          //Input stores the file name for the memory references.

	printf("Replacement: %c  Input File: %s\n", replacement,input); //For error checking

	mainMem *m = newMem(mainbytes);

	printf("\nSimulator output: \n");
	printf("Total address lines required = %d \n", addressLines(m));

	cache *c = newCache(addressLines(m),cachebytes,blocksize,N,replacement);
	printf("Number of bits for offset= %d \n", offBits(c));
	printf("Number of bits for index= %d \n", indexBits(c));
	printf("Number of bits for tag= %d \n", tagBits(c));
	printf("Total cache size required= %d \n\n", totCacheSize(c));
	printf("main memory address\t mmblk#\t cmset#\t cmblk#\t hit/miss\n");

	FILE *fp;
	fp = fopen(input,"r");

	int num_of_addresses=0,i;
	fscanf(fp,"%d", &num_of_addresses);

	int address;  char operation;
	queue *q = newQueue(displayMem);
	
	for (i = 0; i < num_of_addresses; ++i)
	{
		fscanf(fp," %c %d", &operation, &address);
		memLoc *loc = newMemLoc(address,c->blockSize, c->cacheSets, c->assoc);
		enqueue(q,loc);
	}
	fclose(fp);

	displayQueue(stdout,q);
	printf("\n");

	return 0;
}

