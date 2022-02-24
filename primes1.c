#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Test whether n is prime or not. */
int is_prime(unsigned long n) 
{    
    /* We only need to check until sqrt as everything larger would have 
       already been checked as the factors come in pairs. */
    unsigned long max = sqrt(n);
    unsigned long fact;
    for (fact = 2; fact <=max; fact++)
    {
        if (n % fact == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) 
{	
	char *eptr;
	unsigned long n, i;
    
	if (argc < 2) {
		printf("Please specify the size.\n");
		return 1;
	}
	n = strtol(argv[1], &eptr, 10);
	printf("Calculating all primes below %ld.\n", n);
    
    printf("%lu ", 2L);
    for (i = 3; i < n; i+=2) 
    {
        if (is_prime(i)) 
        {
            printf("%lu ", i);
        }
    } 
    printf("\n");

    return 0;
}
