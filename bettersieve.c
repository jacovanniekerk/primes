#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void better_sieve(unsigned long* p, unsigned long n)
{
    unsigned long *m;
    unsigned long i, j, limit, cnt;
    char is_prime;

    /* Create space for the the multiples as well */
    m = (unsigned long *) malloc(sizeof(unsigned long) * n);

    /* prime the list with the first prime number */
    p[0] = m[0] = 2;
    cnt = 1;              

    for (i=3; cnt <= n; i+=2)
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
        }
    }

    free(m);
}

int main(int argc, char *argv[])
{
	char *eptr;
	long size, i;    
    unsigned long *p;
    
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
    better_sieve(p, size);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    for (i = 0; i < size; i++)
    {
        printf("%lu ", p[i]);
    }

    printf("\n\ntime used: %f\n", cpu_time_used);

    free(p);
    
    return 0;
}
