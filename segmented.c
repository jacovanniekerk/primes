#include <stdio.h>
#include <stdlib.h>

void sieve(char* ptr, unsigned long size)
{
	unsigned long i, j;

	/* Assume all numbers are prime and then the sieve will mark the 
	   composites. */	
	for(i = 1; i <= size; i++)
	{
		ptr[i] = 1;
	}

	/* Start with the smallest prime number, which is 2. No need to check for 
	   numbers greater than square root of n as the smaller member of the 
	   factor-pair would already have marked it. */	   
	for(i = 2; i*i <= size; i++)
	{
		if(ptr[i])
		{
			/* Mark all the multiples of i as -1. We can start at the square 
			   thanks to the PNT.  Since all composites are the product of a
			   unique set of primes, the smallest composite that has NOT yet
			   been marked off is i*i. */
			for(j = i*i; j <= size ; j += i)
				ptr[j] = 0;
		}
	}
}

int main(int argc, char *argv[])
{
		
	char *ptr, *eptr;	
	unsigned long size;

	if (argc < 2) {
		printf("Please specify the size.\n");
		return 1;
	}

	size = strtol(argv[1], &eptr, 10);
	printf("Calculating all primes below %ld.\n", size);

	ptr = (char *)malloc(sizeof(char)*size);

	if (ptr == NULL) 
	{
		printf("Not enough memory");
		return 1;
	}
	
	sieve(ptr, size);
	
	/*
	printf("Prime numbers are: \n");
	for(i=2; i <= size; i++)
	{
		if(ptr[i] != 0)
		{
			printf("%lu ", i);
		}

	}    
	printf("\n");*/
   
	free(ptr);

	return 0;

}