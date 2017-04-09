#include<stdio.h>
#include<stdlib.h>

int main(){

	char repl;
	char FIFO = 'F';
	printf("Replacement?");
	scanf(" %c", &repl);
	
	if(repl == FIFO)
	{
		printf("working\n");
	}


	return 0;
}