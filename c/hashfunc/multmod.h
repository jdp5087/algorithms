#include <gmp.h>


struct hash_descriptor {
	mpz_t p;
	mpz_t a;
	mpz_t b;
	mpz_t m;
};

void init_hash_func_descriptor(unsigned long modulus);
void rebuild_increase(unsigned long multiplier);
void rebuild_decrease(unsigned long multiplier);
unsigned long hash(void *key);


