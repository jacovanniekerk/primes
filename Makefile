CC=gcc

all: primes1 sieve incsieve segmented

primes1: primes1.c
	$(CC) -ansi -pedantic -Wall -Werror primes1.c -o primes1 -lm

sieve: sieve.c
	$(CC) -ansi -pedantic -Wall -Werror sieve.c -o sieve -lm

incsieve: incsieve.c
	$(CC) -ansi -pedantic -Wall -Werror incsieve.c -o incsieve -lm

segmented: segmented.c
	$(CC) -ansi -pedantic -Wall -Werror -pg segmented.c -o segmented -lm

clean:
	rm -f primes1 sieve incsieve segmented
     
