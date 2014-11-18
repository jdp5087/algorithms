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

#include <gmp.h>

#include "multmod.h"

struct hash_descriptor desc;

void init_hash_func_descriptor(unsigned long modulus)
{
	mpz_init(desc.p);
	mpz_init(desc.a);
	mpz_init(desc.b);
	mpz_init(desc.m);

	mpz_set_ui(desc.m, modulus);
}



int main()
{
	mpz_t sum;
	
}
