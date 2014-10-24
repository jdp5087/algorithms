#define WORD_WIDTH 32
#define MAX_MODULUS (1 << ((WORD_WIDTH)/2))

/* value of s in miller rabin, will
   yield a probability of (1/(2**30))
   that miller_rabin falsely reports
   a non-prime to be prime */
#define MILLER_RABIN_ATTEMPTS 30 

struct t_and_u {
	unsigned long t;
	unsigned long u;
};

unsigned long find_prime(unsigned long l, unsigned long h);
