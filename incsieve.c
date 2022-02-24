#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct node {
    unsigned long p;
    unsigned long m;
    struct node * next;
} node_t;

/* add the element to the linked list */
int add(node_t **tail, unsigned long prime)
{
    (*tail)->next = (node_t *) malloc(sizeof(node_t));    
    if ((*tail)->next == NULL) return 1;    
    (*tail)->next->p = prime;
    (*tail)->next->m = prime;
    (*tail)->next->next = NULL;
    (*tail) = (*tail)->next;        
    return 0;
}

/* free memory */
void del(node_t **head) {
    node_t *tmp;
    while ((*head) != NULL) 
    {   
        tmp = (*head);
        *head = (*head)->next;
        free(tmp);
    }
}

int main(int argc, char *argv[])
{
    /* Variables pointers into linked list */
    node_t *head, *tail, *runner;

	char *eptr;
	long size, i;
    char is_prime;
    long limit;

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
	printf("Calculating all primes below %ld.\n", size);

    /* Prepare the storage on the heap (assume storage was successful) */

    start = clock();

    head = tail = (node_t *) malloc(sizeof(node_t));
    head->p = head->m = 2;
    head->next = NULL;
      
    /* Run the actual sieve */
    /*printf("2 ");*/

    for (i=3; i < size; i+=2)
    {
        limit = sqrt(i);
        runner = head;
        is_prime = 1;
        while (runner != NULL) 
        {   
            if (runner->p > limit) break;
            while (runner->m < i) runner->m += runner->p;
           
            if (runner->m == i) {
                is_prime = 0;
                break;
            } 
            runner = runner->next;        
        }

        if (is_prime) 
        {
            if (add(&tail, i))
            {
                printf("Out of memory..."); /* Not really done these days... */ 
                return 1;
            }
            /*printf("%lu ", i);*/
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("time used: %f\n", cpu_time_used);


    /*printf("\n");*/

    /* The list contains all primes under size, except 2.  If the list is 
       needed elsewhere, simply add 2 before returning.  Since  we do not in 
       this case, we can simply free the memory and return.  */
    
    del(&head);
    return 0;
}
