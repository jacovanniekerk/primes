#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long u32;

typedef struct node
{
    u32 data;
    struct node *next;
} node_t;

/* Add the new prime to the end of the list. */
int enqueue(node_t **tail, u32 prime)
{
	/* Create a new node. */
	node_t *element = (node_t *) malloc(sizeof(node_t));
	
	if (element == NULL) {
		printf("Out of memory!");
		return 1;
	}

	element->data = prime;
    element->next = NULL;
	
	/* If tail is empty, then the list is currently empty. */
	if ((*tail) == NULL)
	{
		*tail = element;
		return 0;
	}
	        
    *tail = (*tail)->next = element;
    return 0;
}

/* Free the memory used by the linked list. */
void del(node_t **head)
{
	node_t *tmp;
    while ((*head) != NULL) 
    {   
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }	
}

u32 print_primes(node_t *head)
{
	node_t *runner = head;
	int count = 0;
    while (runner != NULL) 
    {   
		/*printf("%lu ", runner->data);	*/
        runner = runner->next;       
		count++; 
    }
	return count;
}

void sieve(char* ptr, u32 size)
{
	u32 i, j;

	/* Assume all numbers are prime and then the sieve will mark the 
	   composites. */
    ptr[0] = ptr[1] = 0;	
	for(i = 2; i <= size; i++)
	{
		ptr[i] = 1;
	}

	/* Start with the smallest prime number, which is 2. No need to check for 
	   numbers greater than square root of n as the smaller member of the 
	   factor-pair would already have marked it. */	   
	for(i = 2; i * i <= size; i++)
	{
		if(ptr[i])
		{
			/* Mark all the multiples of i as -1. We can start at the square 
			   thanks to the PNT.  Since all composites are the product of a
			   unique set of primes, the smallest composite that has NOT yet
			   been marked off is i*i. */
			for(j = i * i; j <= size ; j += i)
			{
				ptr[j] = 0;
			}
		}
	}
}

void segmented_sieve(char* ptr, u32 low, u32 high, node_t *head)
{
    u32 size, i, j, p, lo;

    /* Calculate the size of the segment, mark all as possibly prime. */
    size = high - low + 1;
    for(i = 0; i < size; i++)
	{
		ptr[i] = 1;
	}

    /* Use the found primes to mark the multiples. */    
    while (head != NULL)
    {
        p = head->data;

        /* Over the limit yet? */
        if (p * p > high) break;

        /* Find the minimum number in [low..high] that is a multiple of p. */
        lo = ((low + p - 1) / p) * p;		

        /* Mark multiples of p in [low..high).  We need to offset the number
           by low, since the segment starts at 0. */
        for (j = lo; j < high; j += p)
        {
            ptr[j-low] = 0;
        }		

		/* Move to next prime number. */
		head = head->next;
    }            
}


void grab_primes(char* ptr, u32 n, u32 offset, node_t **tail)
{
    u32 i;
	for (i = 0; i < n; i++)
	{		
		if (ptr[i])
		{
			enqueue(tail, i + offset);
			
		}
	}
}

node_t *go(u32 max)
{	
	node_t *tail = NULL, *head = NULL;
	u32 limit, low, high;
	char *ptr;

	/* We want all primes less than 'max'.  The factors of any number comes in
	   pairs (a small number and a large number).  For a prime number p, the 
	   only pair is 1 and p.  For non-primes there are more, for example for 
	   20 we have: 1x20; 2x10; 4x5; 5x4; 10x2; 20x1.  The numbers repeat at 
	   the square root of a number, i.e. for 20 that is between 4 and 5.  This
	   means we ONLY have to check up to and incl. the square root of a number 
	   to determine if it's prime as these will all be the smaller number, that
	   means: 2 and 3 for all numbers 16 to 24. 
	   
	   We start by calculating all primes under the square root of max (using
	   the normal sieve), since we only need to use these to check for primes 
	   under max. After that we put them into the list. */
	limit = sqrt(max) + 1;
	ptr = (char *)malloc(sizeof(char) * (limit + 1));
	sieve(ptr, limit);
	ptr[0] = ptr[1] = ptr[2] = 0;

	/* Copy unmarked elements (i.e. primes) into the linked list. */
	enqueue(&tail, 2);
	head = tail;
    grab_primes(ptr, limit, 0, &tail);

    /* Since we already have a ptr, just use it as the segment size as well.  
       Second segment to traverse is from limit to limit */
    low = limit;
    high = 2*limit;
    
    /* Keep going while there are segments left. */
    while (low < max)
    {
        if (high > max) high = max; /* Ensure upper bound is under max. */

		if (high-low+1>(limit+1)){
			printf("problem found");
		}

        segmented_sieve(ptr, low, high, head);
        grab_primes(ptr, high - low, low, &tail);

        /* Move to next segment. */
        low = low + limit;
        high = high + limit;		
    } 
	free(ptr);
	return head;
}

int main(int argc, char *argv[])
{		
	/* Read command-line parameter */	
	char *eptr;	
	u32 size;
	node_t *p;

	if (argc < 2) {
		printf("Please specify the size.\n");
		return 1;
	}
	size = strtol(argv[1], &eptr, 10);
	printf("Calculating all primes below %ld.\n", size);

	p = go(size);	
	printf("Prime numbers are: \n");
	size = print_primes(p);
	del(&p);
	printf("\nFound %lu.\n", size);
	return 0;
}
