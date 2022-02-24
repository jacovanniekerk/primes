#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 100000

typedef struct node {
    unsigned long p[MAX];
    unsigned long m[MAX];
    struct node * next;
} node_t;

/* add the element to the linked list of arrays */
int add(node_t **tail, unsigned int *cnt, unsigned long prime)
{
    /* How much space left in tail. */
    if (*cnt == MAX)
    {
        /*printf("[%lu] ", prime);*/
        (*tail)->next = (node_t *) malloc(sizeof(node_t));
        if ((*tail)->next == NULL) 
        {
            return 1;
        }
        (*tail) = (*tail)->next;
        *cnt = 0;
    } 
    
    (*tail)->p[*cnt] = (*tail)->m[*cnt] = prime;
    (*cnt)++;    
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
	long size, i, j, tot;
    char is_prime;
    long limit;
    unsigned int cnt = 0;

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
    head->p[0] = head->m[0] = 2;
    head->next = NULL;
    cnt = 1;
      
    /* Run the actual sieve */
    /*printf("2 ");*/

    for (i=3; i < size; i+=2)
    {
        limit = sqrt(i);
        runner = head;
        is_prime = 1;
        while (runner != NULL && is_prime) 
        {   
            tot = runner == tail ? cnt : MAX; 
            for (j = 0; j < tot && is_prime; j++) 
            {

                if (runner->p[j] > limit) break;
                while (runner->m[j] < i) runner->m[j] += runner->p[j];
           
                if (runner->m[j] == i) {
                    is_prime = 0;                    
                }
            }
            runner = runner->next;        
        }

        if (is_prime) 
        {
            if (add(&tail, &cnt, i))
            {
                printf("Out of memory..."); /* Not really done these days... */ 
                return 1;
            }
            /*printf("%lu ", i);*/
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    


    /* print to test */ 
    runner = head;
    while (runner != NULL) 
    {   
        tot = runner == tail ? cnt : MAX; 
        for (j = 0; j < tot; j++) 
        {
            printf("%lu ", runner->p[j]);                                           
        }
        runner = runner->next;        
        printf("\n");
    }

    printf("time used: %f\n", cpu_time_used);    

    /* The list contains all primes under size, except 2.  If the list is 
       needed elsewhere, simply add 2 before returning.  Since  we do not in 
       this case, we can simply free the memory and return.  */
    
    del(&head);
    return 0;
}
