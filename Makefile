CC=gcc

all: primes1 sieve incsieve incsieve2 incsieve3 bettersieve segmented

primes1: primes1.c
	$(CC) -ansi -pedantic -Wall -Werror primes1.c -o primes1 -lm

sieve: sieve.c
	$(CC) -ansi -pedantic -Wall -Werror sieve.c -o sieve -lm

incsieve: incsieve.c
	$(CC) -ansi -pedantic -Wall -Werror incsieve.c -o incsieve -lm


incsieve2: incsieve2.c
	$(CC) -ansi -pedantic -Wall -Werror incsieve2.c -o incsieve2 -lm

incsieve3: incsieve3.c
	$(CC) -ansi -pedantic -Wall -Werror incsieve3.c -o incsieve3 -lm

bettersieve: bettersieve.c
	$(CC) -ansi -pedantic -Wall -Werror bettersieve.c -o bettersieve -lm

segmented: segmented.c
	$(CC) -ansi -pedantic -Wall -Werror segmented.c -o segmented -lm

clean:
	rm primes1 sieve incsieve incsieve2 incsieve3 bettersieve segmented
     
