
#include <stdio.h>
#include <string.h>

#include "../prime/prime.h"
#include "search.h"
#include "../linked_list/linked_list.h"

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


/*
  Create a hash for first n characters,
  using r as radix.
 */
void matcher(struct entry *entries, struct print_stack *stack, 
	     struct rolling_hash *t, struct rolling_hash *p,
	     unsigned long r, unsigned long q)
{
	unsigned long i, m, n, high_r;
	void *tmp;
	
	m = p->n;
	n = t->n;
	high_r = modexp(r, m - 1, q);

	for (i = 0; i < m; i++) {
		p->h = (r*p->h + p->s[i]) % q;
		t->h = (r*t->h + t->s[i]) % q;
	}

	for (i = 0; i < (n - m); i++) {
		if (p->h == t->h) {
			if (strings_equal(p->s, 0, t->s, i, p->n)) {
				add_entry(i, 1, entries, stack);
				add_entry(i + m, -1, entries, stack);
			}
		}
		if (i < (n - m))
			t->h = (r*(t->h - t->s[i]*high_r) + t->s[i + m]) % q;
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
	char *line[BUF_LEN];
	struct print_stack stack;
	struct entry entries[BUF_LEN];
	init_print_stack(&stack);

	struct rolling_hash text_hash;
	struct rolling_hash pattern_hash;

	unsigned long m, i, prime_modulus;



	m = stringlength(p);

	init_rolling_hash(&pattern_hash, p, m);

	prime_modulus = find_prime(m + 1, MAX_MODULUS);

	for (i = 0; i < m; i++) {
		pattern_hash->h = (RADIX*pattern_hash + pattern_hash->s[i]) % prime_modulus
	}
	

	int lineno = 0;
	
	while (stat->done != 1) {
		readline(line, BUF_LEN, fp, &stat);
		init_rolling_hash(&text_hash, line, stat->len);
		matcher(entries, &stack, &text_hash, &pattern_hash, RADIX, prime_modulus);
		print_colored_line(line, lineno, entries, &stack);
		lineno++;
	}
}
