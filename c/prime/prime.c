#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


int bitwise_length(unsigned long n)
{
	unsigned long x = n;
	int i = 0;
	while (x) {
		x >>= 1;
		i++;
	}
	return i;
}

static inline get_bit(unsigned long x, int bit)
{
	return x & (1 << (bit - 1));
}

unsigned long modexp(unsigned long a, unsigned long b, unsigned long n)
{
	unsigned long d = 1, kbit;
	int k = bitwise_length(b);
	
	for (k; k > 0; k--) {
		d = (d * d) % n;
		kbit = get_bit(b, k);
		if (kbit)
			d = (d * a) % n;
	}
	return d;
}

/*
  Ok, for witness, we have to know a little bit about the properties of prime numbers in binary.
  They start with 1 and end with 1. Therefore, if we are given an even number, immediately return true
  (obvious). Otherwise, we subtract one, and shift the number right t times until the furthest right bit
  is no longer 0. This guarantees our number remaining is u, which is definitely odd (because the 1 column
  is on). Then we have n-1 = (2**t)*u, and we are all set to jump in to the rest of the algorithm.
 */

void get_t_and_u(struct t_and_u *s, unsigned long x)
{
	s->t = 0;
	s->u = x;
	
	while (!(s->u & 1)) {
		s->t++;
		s->u >>= 1;
	}

}

/* witness returns true if the number is composite */
int witness(unsigned long a, unsigned long n)
{
	unsigned long i, t, u, xcur, xprev;
	struct t_and_u tu;
	
	if ((!(n & 1)) && (n != 2)) /* n is a multiple of 2, so not prime */
		return 1;

	get_t_and_u(&tu, (n - 1));

	xcur = modexp(a, tu.u, n);

	for (i = 0; i < tu.t; i++) {
		xprev = xcur;
		xcur = modexp(xprev, 2, n);
		if ((xcur == 1) && (xprev != 1) && (xprev != (n - 1))) {
			printf("nontrivial square root of 1 mod n\n");
			return 1;
		}
	}
	if (xcur != 1) {
		printf("a**(n-1) is not congruent to 1 mod n\n");
		return 1;
	}
	return 0;
}

/* returns true if prime, false if composite */
int miller_rabin(unsigned long n, int s)
{
	int j;
	unsigned long a;

	if (n > MAX_MODULUS) {
		printf("The use of a modulus larger than %d on a %d-bit sytem might overflow.\n",
		       MAX_MODULUS,
		       WORD_WIDTH);
		exit(1);
	}

	for (j = 0; j < s; j++) {
		a = ((unsigned long)rand() % (n - 1)) + 1;
		if (witness(a, n))
			return 0;
	}
	return 1;
}

/*
  if high > MAX_MODULUS, We reduce high to MAX_MODULUS and continue.
   will return a prime where l <= p <= h, or NULL if no prime found
 */
unsigned long find_prime(unsigned long l, unsigned long h)
{
	
	unsigned long p, tmp;
	if (h < l) {
		tmp = h;
		l = h;
		l = tmp;
	}
	
	if (h > MAX_MODULUS) {
		printf("Warning: reducing high value to %d to avoid overflow\n", MAX_MODULUS);
		h = MAX_MODULUS;
	}
	/* Lean towards higher values, because we want to reduce number of collisions
	   in hash function using the largest possible modulus */
	for (p = h; p > l; p--) {
		if (miller_rabin(p, MILLER_RABIN_ATTEMPTS))
			return p;
	}
	return 0;
}



int main(int argc, char *argv[])
{
	srand(time(NULL));
	unsigned long i;
	printf("%lu\n", find_prime(MAX_MODULUS - 1000, MAX_MODULUS));
	return 0;
}
