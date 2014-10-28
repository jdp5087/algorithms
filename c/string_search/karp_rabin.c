
#include <stdio.h>
#include <string.h>

#include "../prime/prime.h"
#include "search.h"
#include "karp_rabin.h"

/*
  This name can't be an accident...
 */
struct rolling_hash {
	char *s;
	unsigned long n;
	unsigned long h;
};

/*
  This is necessary because strlen in string.h requires const char *,
  which our strings might not be.
 */
unsigned long stringlength(char *s)
{
	unsigned long n = 0;
	char *sp = s;

	while (*sp != '\0') {
		n++;
		sp++;
	}
	return n;
}

int strings_equal(
	char *first,
	unsigned long first_offset,
	char *second,
	unsigned long second_offset,
	unsigned long length
	)
{
	unsigned long i;
	char *s1, *s2;

	s1 = first + first_offset;
	s2 = second + second_offset;

	for (i = 0; i < length; i++) {
		if (*(s1++) != *(s2++))
			return 0;
	}
	return 1;
	
}

void init_rolling_hash(struct rolling_hash *rh, char *s, unsigned long stringlen)
{
	rh->s = s;
	rh->n = stringlen;
	rh->h = 0;
}


/* I was experiencing problems with underflow
   since this algorithm uses unsigned longs. The problem came from a case
   where t->h was less than t->s[i]*high_r. Fortunately, a little modular
   arithmetic helped solve the problem.
   
   we will take advantage of this fact (let ~ represent congruence):
   
   0 ~ q mod q
   -(a mod q) + (a mod q) ~ q mod q
   -(a mod q) ~ (q mod q) - (a mod q)
   -(a mod q) ~ ((q - (a mod q)) mod q)
   
   so starting with the original formula:
   
   ((r*(t->h - t->s[i]*high_r) + t->s[i+m]) mod q)
   
   ~
   
   (r*t->h - r*t->s[i]*high_r + t->s[i+m]) mod q
   
   ~
   
   (((r*t->h mod q) - (r*t->s[i]*high_r mod q) + (t->s[i+m] mod q)) mod q)
   
   ~
   
   (((r*t->h mod q) + ((q - (r*t->s[i]*high_r mod q)) mod q) + (t->s[i+m] mod q)) mod q)
   
   ~
   
   ((r*t->h + (q - (r*t->s[i]*high_r mod q)) + t->s[i+m]) mod q)
   
   Note that overflow is not a concern because the prime modulus is chosen so that
   
   (prime_modulus)**2 < MAX_LONG so as long as RADIX < prime_modulus, overflow will not happen
   because outside of modexp the largest mutliplication possible is (prime_modulus - 1)*RADIX

   A 64-bit system would be great because it would allow our prime_modulus to be <= (1 << 32)
   instead of (1 << 16), giving us FAR fewer hashing collisions. However, I think we are already
   doing pretty well here.
*/
void matcher(struct entry *entries, struct print_stack *stack, 
	     struct rolling_hash *t, struct rolling_hash *p,
	     unsigned long r, unsigned long q)
{
	unsigned long i, m, n, high_r;

	unsigned long high_char;

	m = p->n;
	n = t->n;

	if (n < m)
		return;
	
	high_r = modexp(r, m - 1, q);

	for (i = 0; i < m; i++)
		t->h = (r*t->h + t->s[i]) % q;

	for (i = 0; i < (n - m); i++) {
		if (p->h == t->h) {
			if (strings_equal(p->s, 0, t->s, i, m)) {
				add_entry(i, 1, entries, stack);
				add_entry(i + m, -1, entries, stack);
			}
		}
		if (i < (n - m)) {
			high_char = high_r * t->s[i];
			if (t->h >= high_char)
				t->h = ((r*(t->h - high_char) + t->s[i+m]) % q);
			else
				t->h =  ((r*t->h + (q - (r*high_char % q)) + t->s[i + m]) % q);
		}

	}
}

/* REMEMBER TO CHANGE PRIME TEST!
   CURRENTLY IT IS DETERMINISTIC (RETURNS HIGHEST PRIME IN RANGE)
   THEREFORE CANNOT RELY ON THE ASSUMPTION OF SIMPLE RANDOM HASH
   IF RANDOMIZED THIS WILL BE FIXED, SACRIFICING A POSSIBLY SMALLER
   PRIME MODULUS FOR RANDOMIZED BEHAVIOR
 */

void karp_rabin(FILE *fp, char *p)
{
	struct read_status stat;

	char line[BUF_LEN];
	struct print_stack stack;
	struct entry entries[BUF_LEN];
	init_print_stack(&stack);

	struct rolling_hash text_hash;
	struct rolling_hash pattern_hash;

	unsigned long m, i, prime_modulus;
	int lineno = 0;
	stat.done = 0;

	m = stringlength(p);

	init_rolling_hash(&pattern_hash, p, m);

	prime_modulus = find_prime(m + 1, MAX_MODULUS);

	for (i = 0; i < m; i++)
		pattern_hash.h = (RADIX*pattern_hash.h + pattern_hash.s[i]) % prime_modulus;
	
	do {
		readline(line, BUF_LEN, fp, &stat);
		init_rolling_hash(&text_hash, line, stat.len);
		if (stat.len != 0)
			matcher(entries, &stack, &text_hash, &pattern_hash, RADIX, prime_modulus);
		if (!empty_stack(&stack))
			print_colored_line(line, lineno, entries, &stack);
		reset_stack(&stack);
		lineno++;
	} while (!stat.done);
}

			/* printf("starting t->h: %lu\n", t->h); */
			/* t->h = t->h - (t->s[i]*high_r); */
			/* printf("subtract result: %lu\n", t->h); */
			/* t->h = t->h*r; */
			/* printf("times r: %lu\n", t->h); */

			/* t->h = t->h + t->s[i + m]; */
			/* printf("plus end char: %lu\n", t->h); */

			/* t->h = t->h % q; */
			/* printf("modulo q: %lu\n", t->h); */
