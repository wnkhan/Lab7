#include<stdio.h>
#include<stdlib.h>

int main(){

	int num_of_addresses;
	FILE *filepointer;

	filepointer = fopen("example_test_data.txt", "r");

	fscanf(filepointer, "%d", &num_of_addresses);

	printf("%d \n\n", num_of_addresses);

	int i,j;

	int refnum[num_of_addresses];
	char memop[num_of_addresses];
	for(i=0; i<num_of_addresses;i++)
	{
		fscanf(filepointer,"%s %d", &memop[i], &refnum[i]);
	}

	char headings[] = {"main memory address   mm blk #   cm set #   cm blk #   hit/miss"};
	char underline[] = {"_________________________________________________________________"};

	printf("%s\n", headings);
	printf("%s\n", underline);

	for (j = 0; j < num_of_addresses; ++j)
	{
		printf("       %d\n", refnum[j]);
	}
	


	return 0;

}
