#include <errno.h>
#include <gmp.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "multmod.h"
#include "../include/sysvars.h"


/*
  This will be a universal hashing scheme:

  choose a, b < p where p is a prime greater than |U|, m is |table|.

  h_a_b(x) = ((a*x + b) mod p) mod m)

  Probability of a collision is 1/m if a != 0.

  This hash function will be using the gnu multiprecision library for its ability to do
  arithmetic on integers of arbitrary size. I wanted to implement my own numerics
  such as karatsuba, but quickly found that to be a rabbit-hole, and a diversion
  from my current goals. This will be something I return to in the future.

  keys will be stored as a void * to mpz_t type (natural number of arbitrary size).

  Another great part about gmplib is that we get prime pickers and modular operators to boot.

  As with most of the other code I've been writing, I'm going to assume that our table size
  will never exceed MAX_LONG/sizeof(struct linked_list *). Therefore, hash() will return an
  unsigned long, because that will fit just fine. Why? Because my main memory is only
  4 GB currently, and this is mainly a learning exercise, not a production implementation of
  a hash function. With that being said I hope that this will work with decent speed,
  not knowing much about the algorithmic complexity of gmplib functions.
 */


static struct hash_descriptor desc;

gmp_randstate_t state;

/* get a random number > |universe|. Then use that number to
   find the next largest prime (this gives us a very crude
   "random" prime generator). Then find a and b to be random
   numbers between 1 and p-1, and b to be between 0 and p-1.
 */
void init_hash_func_descriptor(unsigned long modulus)
{

	FILE *fp;
	mpz_t universe, tmp, tmp2;

	unsigned long seed;

	
	/* open up /dev/random and read an unsigned long from it */
	if (!(fp = fopen("/dev/random", "r"))) {
		printf("Error while opening %s: %s\n", "/dev/random", strerror(errno));
		exit(1);
	}
	if (1 != fread((void *)&seed, sizeof(seed), 1, fp)) {
		printf("Error while reading from %s\n", "/dev/random");
		exit(1);
	}
	if (fclose(fp) == EOF) {
		printf("Error: %s would not close properly. Info: %s", "/dev/random", strerror(errno));
		exit(1);
	}
	printf("seed: %lu\n", seed);

	/* initialize and seed the random state */
	gmp_randinit_default(state);
	gmp_randseed_ui(state, seed);

	mpz_init(universe);
	mpz_init(tmp);
	mpz_init(tmp2);
	
	mpz_init(desc.p);
	mpz_init(desc.a);
	mpz_init(desc.b);
	mpz_init(desc.m);

	mpz_set_ui(desc.m, modulus);
	
	/* set universe to be 2**WORD_SIZE */
	mpz_ui_pow_ui(universe, 2, WORD_SIZE);
	/* set max random value to be 2**(WORDSIZE*2) */
	mpz_ui_pow_ui(tmp, 2, WORD_SIZE*2);

	mpz_urandomm(tmp, state, tmp);

	/* guarantee our number is greater than or equal to universe */
	mpz_ior(tmp, universe, tmp);

	/* find the next highest prime from our random tmp value */
	mpz_nextprime(desc.p, tmp);

	/* 0 < a < p */
	mpz_sub_ui(tmp, desc.p, 1);
	mpz_urandomm(desc.a, state, tmp);
	mpz_add_ui(desc.a, desc.a, 1);

	/* 0 <= b < p */
	mpz_urandomm(desc.b, state, desc.p);

	gmp_printf("desc.a: %Zd\n", desc.a);
	gmp_printf("desc.b: %Zd\n", desc.b);
	gmp_printf("desc.p: %Zd\n", desc.p);
	gmp_printf("desc.m: %Zd\n", desc.m);
}

void rebuild_increase(unsigned long multiplier)
{
	mpz_t tmp;

	mpz_init(tmp);

	mpz_mul_ui(tmp, desc.m, multiplier);
	
	if (mpz_cmp_ui(tmp, ULONG_MAX) > 0) {
		gmp_printf("Error while increasing hash function modulus: multiplying %Zd"
			   " by %lu would result in a modulus greater than %lu.\n",
			   desc.m, multiplier, ULONG_MAX);
		exit(1);
	}

	mpz_set(desc.m, tmp);
}

void rebuild_decrease(unsigned long multiplier)
{
	mzp_t tmp;

	mpz_init(tmp);

	mpz_fdiv_q_ui(tmp, desc.m, multiplier);

	if (mpz_cmp_ui(tmp, 1) <= 0) {
		printf("Error while decreasing hash function modulus: modulus must not be"
		       " reduced to less than 1. That would sort-of defeat the purpose"
		       " of a hash function.\n");
		exit(1);
	}

	mpz_set(desc.m, tmp);
}
	


