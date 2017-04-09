//William Khan CWID 11498827
//Lab7 -- ECE487

#include<stdio.h>
#include<stdlib.h>

int numberofbits(int num);

int main(){

	char continuity = 'y';

	while(continuity == 'y')
	{

	int mainbytes, cachebytes, blocksize, N;
	char replacement,  input[20];
	char FIFO = 'F';
	char LRU = 'L';

	printf("Enter the size of the main memory in bytes:");
	
	scanf("%d", &mainbytes);    //Main memory size is stored in mainbytes.
	
	printf("Enter the size of the cache in bytes:");
	scanf("%d", &cachebytes);   //Cache size is stored in cachebytes.

	printf("Enter the cache block/line size:");
	scanf("%d", &blocksize);    //Block size is store in blocksize.
	
	printf("\nEnter the degree of set-associativity(input n for an n-way set-associative mapping):");
	scanf("%d", &N);            //N for associativity

	printf("Enter the replacement policy (L=LRU, F=FIFO):");
	scanf(" %c", &replacement);  //Replacement holds the replacement policy for the cache.
	
	printf("Enter the name of the input file containing the list of memory references generated\n");
	printf("by the CPU: ");
	scanf("%s", input);          //Input stores the file name for the memory references.

	int cacheblocks = cachebytes / blocksize;
	int cachesets = cacheblocks / N;	  //The cacheblocks are divided by N(assoc.) to determine the number of cache sets.
	int index = numberofbits(cachesets);  //Numberofbits() determines the number of bits to represenet a given decimal number.


	int addresslines = numberofbits(mainbytes);  //Determines the total number of bytes for the address space.
	int offset = numberofbits(blocksize);		 

	int tag = addresslines - (offset + index);     //Subtracting the bits representing the offset and index from the address space gives the tag.
	int total_cache_size = cachebytes + (tag + 2)*(cacheblocks/8);

	printf("\nSimulator output: \n");
	printf("Total address lines required = %d \n", addresslines);
	printf("Number of bits for offset= %d \n", offset);
	printf("Number of bits for index= %d \n", index);
	printf("Number of bits for tag= %d \n", tag);
	printf("Total cache size required= %d \n\n", total_cache_size);


	//From Read.c
	int num_of_addresses;
	FILE *filepointer;

	filepointer = fopen(input, "r");

	fscanf(filepointer, "%d", &num_of_addresses);  //Stores the first integer from text file and determines number of line reads.

	int a;

	int address[num_of_addresses];
	char memop[num_of_addresses];
	for(a=0; a<num_of_addresses;a++)
	{
		fscanf(filepointer,"%s %d", &memop[a], &address[a]);  //Stores memory operation and address information from text file.
	}

	

	int mmblk_num[num_of_addresses], cmset[num_of_addresses], cmblk[num_of_addresses], b;
	int c, d, mmblk_num1[num_of_addresses], result[num_of_addresses];
	

	//Creates arrays for memory reference table
	for(b=0; b<num_of_addresses; b++)
	{
		mmblk_num[b] = address[b] / blocksize; 
		cmset[b] = mmblk_num[b] % cachesets;
		cmblk[b] = cmset[b] * N;
		mmblk_num1[b] = mmblk_num[b];  //Duplicate copy of memory block number for addresses was made to analyze best hit rate.
		result[b] = 0;
	}

	//Counts the highest number of hits possible for best hit rate.
	int repeat = 0, dwn_cnt = -1;
	for(c=0; c < num_of_addresses; c++)
	{
		for(d=c+1;d < num_of_addresses;d++)       //Walks through the array after first index.
		{
			if (c != d)							  //Avoids identical indices.
			{
				if(mmblk_num[c] == mmblk_num1[d])
				{
					mmblk_num1[d] = dwn_cnt;       //Replaces repeated memory blocks with negative numbers to avoid double counting.
					dwn_cnt--;					   //The negative number is incremente so it is also not double counted.
					repeat++;					   //Determines repeated numbers.
					result[d] = 1;				   //Used to count hits in best hit rate possible.
				}
			}
		}
	}


	//Beginning of Cache memory output code
	
	int f, cachedata[cacheblocks], dirty[cacheblocks], valid[cacheblocks], cache_count[cacheblocks], hits = 0, cmset_count[cacheblocks/N], position;

	for (f = 0; f < (cacheblocks/N); f++)
	{
		cmset_count[f] = 0;               //cmset_count keeps track of the order in which the cache set is filled.
	}

	//Cachedata was used to store main memory blocks in cache
	//dirty was used for the cache dirty bit
	//valid is the cache memory valid bit
	//This for loop was primarily initializing all necessary items in the cache with the exception of the tag.
	for(f = 0; f < cacheblocks; f++)
	{
		cachedata[f] = -1;   //Initialized at -1 to distinguish emtpy and non-empty memory elements.
		dirty[f] = 0;
		valid[f] = 0;
		cache_count[f] = 0;  //The array kept track of how many times a certain cache memory block was used.
	}	

	//This series of nested for loops was used to compare the main memory blocks to what was in the cache.
	int start, end, start1, end1, notfound, location, max;
	for(f=0; f < num_of_addresses; f++)
	{	
		//This second loop has end and start defined as the beginning and end of each cache memory set for
		//the corresponding main memory block.	
		end = (cmset[f] * N) + N;
		notfound = 0;
		for(start = cmset[f] * N; start < end; start++)
		{	
			//This for loop determines if the current main memory block matches any blocks in the set.
			if(cachedata[start] != mmblk_num[f])
			{
				notfound++;		//Determines how many of the blocks in the set do not have the main memory block of concern.
			}

			else if(cachedata[start] == mmblk_num[f] && replacement == LRU)
			{
				cache_count[start]--;     //Cache count is decremented here to keep track of the least recently used memory elements.
				hits++;					  //hit is used later to determine the actual hit rate.
			}
			
		}

		//This conditional is only executed if the number of unmatched cache blocks is equivalent to the set total.
		if(notfound == N)
		{
			int write_count= 0;
			for(start = cmset[f] * N; start < end; start++)
			{	
				//Performs initial read/write for LRU on empty cache blocks
				if(cachedata[start]==-1 && write_count ==0 && replacement == LRU)
				{
					cachedata[start] = mmblk_num[f];
					write_count++;						//Write count prevents the for loop from overwriting the whole set.
					cache_count[start]--;
					break;
				}
				//Replaces filled cache blocks using LRU
				else if(start == end-1 && replacement == LRU)
				{
					start1 = cmset[f] * N;
					end1 = (cmset[f] * N) + N;
					max = cache_count[start1];
					location = start1;
					for(start1 ; start1 < end1; start1++)
					{
						if(cache_count[start1] > max)  //The least decremented cache count for LRU is least recently used.
						{
							max = cache_count[start1];
							location = start1;
						}
					}
					cachedata[location] = mmblk_num[f]; //The index least decremented in the set is replaced by the main memory block.
					write_count++;					    //Same as mentioned before.
					cache_count[location]--;
					break;
				}

				//Performs initial read/write for FIFO and fills empty sets
				else if(cachedata[start]==-1 && write_count ==0 && replacement == FIFO)
				{
					cachedata[start] = mmblk_num[f];
					write_count++;						
					cmset_count[f]++;
					break;
				}
				//Replaces filled cache blocks using FIFO
				else if(start == end-1 && replacement == FIFO)
				{
					position = cmset_count[f] % N;				//Cmset_count tracks each placement of a main memory block into the cache set
					cachedata[position -1] = mmblk_num[f];		//while ignoring any reads or writes to main memory blocks already present in the set
					cmset_count[f]++;							//so that only the cache blocks in the set are replaced consecutively.
					break;										//If you then divide the cmset_count by the number of blocks in the set, the
				}												//remainder is the next location for the main memory block in question.
			}	
		}
	}

	// Setting valid bytes
	int i, j, tagbits[cacheblocks];
	for (i = 0; i < cacheblocks; i++)
	{	
		tagbits[i] = -1;         //Initialized tag array
		if (cachedata[i] > -1 )
		{
			valid[i] = 1;        //Set valid bit for cache blocks containing a main memory block only.
			
		}
		else
		{
			valid[i] = 0;	
		}
	}
	//End setting valid bytes


	//Getting addresses for mmblocks in cache so that the tag can be obtained.
	for(i=0; i < num_of_addresses; i++)
	{
		for(j=0; j < cacheblocks; j++)
		{
			if(mmblk_num[i] == cachedata[j])
			{
				tagbits[j] = address[i];  //Acquires addresses from memory blocks in cache and puts them into the tag array.
			}
			
		}
	}


	//Converting addresses to tag
	int shifted[cacheblocks], remain[cacheblocks][tag];
	for(i=0;i<cacheblocks;i++)
	{
		shifted[i] = ( tagbits[i]>> (offset + index));  //Shifts all the bits but the tag out of each address.
		for(j=0;j<tag; j++)
		{
			remain[i][j] = shifted[i] % 2;				//Number of tag bits is known, so the decimal number is 
			shifted[i] = shifted[i] /2;					//remainder from the division is stored.
		}												//This happens to the be binary in inverted order for the tag.
	}													//remain[i][j] is where the inverted binary for each tag in the cache is kept.

	//Printing for data in memory access table
	char headings[] = {"main memory address     \tmm blk # \tcm set # \tcm blk # \thit/miss"};
	char underline[] = {"___________________________________________________________________________________________"};

	printf("%s\n", headings);
	printf("%s\n", underline);

	char hit[] = {"hit"};
	char miss[] = {"miss"};

	int e;
	for (e = 0; e < num_of_addresses; ++e)
	{
		printf("\t%d  \t\t\t%d \t\t%d \t\t%d to %d", address[e], mmblk_num[e], cmset[e], cmblk[e], cmblk[e] + (N-1));

		if(result[e]==1)
		{
			printf("\t\t%s\n", hit);
		}
		else
		{
			printf("\t\t%s\n", miss);
		}
	}
	//End of printing for memory access table.

	float hit_rate = (float) repeat/num_of_addresses;
	float actual_hit_rate = (float) hits/num_of_addresses;
	printf("\nHighest possible hit rate = %d/%d = %.2f%% \n", repeat, num_of_addresses, hit_rate*100);
	printf("Actual hit rate = %d/%d = %.2f%% \n", hits, num_of_addresses, actual_hit_rate*100);


	//Printing for final status of the cache
	printf("\nFinal \"status\" of the cache:\n");
	printf("   Cache blk# \t Dirty bit \t Valid bit \t Tag \t Data\n");
	printf("_______________________________________________________________\n");
	
	for(f=0;f<cacheblocks;f++)
	{
		printf("\t%d \t\t%d \t\t%d \t", f, dirty[f], valid[f]);
		if (cachedata[f] > -1)
		{
			for(j=tag-1; j > -1; --j)              //This for loop starts at the end of the array in order to print the binary
			{									   //for the tag in the correct order.
				printf("%d", remain[f][j]);		
			}	
			printf(" \t mm blk # %d\n", cachedata[f]);
		}
		else
		{
			printf("xxx \t xxx\n");
		}
	}

	printf("Continue? (y = yes, n = no): \n");
	scanf(" %c", &continuity);

	}

	return 0;

}
  //End of main()


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