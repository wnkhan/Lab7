//Lab7 -- ECE487
#include <stdio.h>
#include <stdlib.h>
#include "mainMem.h"
#include "cache.h"
#include "queue.h"
#include "sll.h"
#include "darray.h"


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

	int num_of_addresses=0,i,j, count=0;
	fscanf(fp,"%d", &num_of_addresses);

	int address;  char operation;
	DArray *memOps = newDArray(displayMem);

	int mmblk_list[num_of_addresses];

	for (i = 0; i < num_of_addresses; ++i)
	{
		fscanf(fp," %c %d", &operation, &address);
		memLoc *loc = newMemLoc(address,CacheBlockSize(c), CacheSets(c), Associativity(c));
		mmblk_list[i] = getMMBlk(loc);
		for (j=i-1; j >= 0; --j)
		{	
			if (mmblk_list[i] == mmblk_list[j])
			{
				count++;
				loc->hit_miss = "hit";
				break;
			}
		}
		insertDArray(memOps,loc);
	}
	fclose(fp);

	displayDArray(stdout,memOps);
	printf("\nHighest possible hit rate %d/%d = %.02f%%\n", count, num_of_addresses, ((float)count/(float)num_of_addresses)*100);
	printf("\n");

	DArray *DcacheSets[CacheSets(c)];
	queue *QcacheSets[CacheSets(c)];

	for (i = 0; i < CacheSets(c); ++i)
	{
		DcacheSets[i] = newDArray(displayC);
		QcacheSets[i] = newQueue(displayC);
		for (j = 0; j < Associativity(c); ++j)
		{
			insertDArray(DcacheSets[i], NULL);
		}
	}

	//Only for FIFO operations
	for (i = 0; i < num_of_addresses; ++i)
	{
		int found = 0;
		memLoc *Op = getDArray(memOps, i);

		cacheBlock *cblock = newCBlock(getMMBlk(Op));
		if (sizeQueue(QcacheSets[getCSet(Op)]) > 0)  //If the cache set is not empty check for hit
		{
			for (j = 0; j < sizeQueue(QcacheSets[getCSet(Op)]); ++j)
			{
				if (getMMBlk(Op) == getData(getDArray(DcacheSets[getCSet(Op)],j)))
				{
					found = 1;
					break;
				}
			}
		}
		if (found != 1)
		{
		
			if (sizeQueue(QcacheSets[getCSet(Op)]) != Associativity(c)) //If cache set is not full insert
			{
				enqueue(QcacheSets[getCSet(Op)], cblock);
				//Set next empty slot in CacheSet for DArray
				setDArray(DcacheSets[getCSet(Op)],sizeQueue(QcacheSets[getCSet(Op)])-1, cblock);
			}
			else               //If cache set is full replace something
			{
				cacheBlock *removed = dequeue(QcacheSets[getCSet(Op)]);
				for (j = 0; j < Associativity(c); ++j)
				{
					if (getData(removed) == getData(getDArray(DcacheSets[getCSet(Op)],j)))
					{
						break;
					}
				}
				setDArray(DcacheSets[getCSet(Op)], j, cblock);
				enqueue(QcacheSets[getCSet(Op)], cblock);
			}
		}
	}

	// for (i = 0; i < CacheSets(c); ++i)
	// {
	// 	printf("Cache Set Queue %d\n", i);
	// 	displayQueue(stdout, QcacheSets[i]);
	// 	printf("\n");
	// }


	for (i = 0; i < CacheSets(c); ++i)
	{
		for (j = 0; j < Associativity(c); ++j)
		{
			if (getDArray(DcacheSets[i],j)==NULL)
			{
				cacheBlock *emptySlot = newCBlock(-1);
				setDArray(DcacheSets[i], j, emptySlot);
			}
		}
	}

	for (i = 0; i < CacheSets(c); ++i)
	{
		//printf("Cache sets for DArray %d\n", i);
		displayDArray(stdout,DcacheSets[i]);
		//printf("\n");
	}

	return 0;
}
