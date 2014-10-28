#ifndef PRIME_HEADER
#define PRIME_HEADER

#define WORD_WIDTH 32
#define MAX_MODULUS (1 << ((WORD_WIDTH)/2))

/* Value of s in miller rabin, will
   yield a probability of (1/(2**MILLER_RABIN_ATTEMPTS))
   that miller_rabin falsely reports
   a non-prime to be prime. */
#define MILLER_RABIN_ATTEMPTS 30 

/* Used to split a number into an
   odd prefix u and 2**t. Necessary
   becuase two values are produced
   and only one value can be returned. */
struct t_and_u {
	unsigned long t;
	unsigned long u;
};

unsigned long modexp(unsigned long a, unsigned long b, unsigned long n);
unsigned long find_prime(unsigned long l, unsigned long h);

#endif /* PRIME_HEADER */
