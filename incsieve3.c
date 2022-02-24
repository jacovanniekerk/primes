#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[])
{
    /* Variables pointers into linked list */    
	char *eptr;
	long size, i, j;
    char is_prime;
    long limit;

    unsigned long *p, *m;
    unsigned long cnt = 1;

    /* for timing */
    clock_t start, end;
    double cpu_time_used;

    /* Get upper limit */
	if (argc < 2) {
		printf("Please specify the size.\n");
		return 1;
	}

    /* Read the command line parameter and parse it as a long */
	size = strtol(argv[1], &eptr, 10);
	printf("Calculating first %ld primes.\n", size);

    /* Prepare the storage on the heap (assume storage was successful) */

    start = clock();

    p = (unsigned long *) malloc(sizeof(unsigned long) * size);
    m = (unsigned long *) malloc(sizeof(unsigned long) * size);

    p[0] = m[0] = 2;
      
    /* Run the actual sieve */
    /*printf("2 ");*/
    
    for (i=3; i <= size; i+=2)
    {
        limit = sqrt(i);
        is_prime = 1;
        for (j = 0; j < cnt; j++) 
        {   
            if (p[j] > limit) break;
            while (m[j] < i) m[j] += p[j];
           
            if (m[j] == i) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) 
        {
            p[cnt] = m[cnt] = i;
            cnt++;
            /*printf("%lu ", i);*/
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    for (i = 0; i < cnt; i++)
    {
        printf("%lu ", p[i]);
    }


    printf("\n\ntime used: %f\n", cpu_time_used);


    /*printf("\n");*/




    /* The list contains all primes under size, except 2.  If the list is 
       needed elsewhere, simply add 2 before returning.  Since  we do not in 
       this case, we can simply free the memory and return.  */
    
    return 0;
}
