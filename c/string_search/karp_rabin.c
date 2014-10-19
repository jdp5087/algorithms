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

void init_rolling_hash(struct rolling_hash *rh, char *s)
{
	rh->s;
	rh->n = stringlength(s);
	rh->h = 0;
}

void karp_rabin(FILE *t, char *p)
{
	struct read_status stat;
	
}

/*
  Create a hash for first n characters,
  using r as radix.
 */
struct linked_list * matcher(
	struct linked_list *matches,
	struct rolling_hash *t,
	struct rolling_hash *p,
	unsigned long r,
	unsigned long q
	)
{
	unsigned long i, m, n, high_r;
	void *tmp;
	
	m = p->n;
	n = t->n;
	high_r = modexp(r, m-1, q);

	for (i = 0; i < m; i++) {
		p->h = (r*p->h + p->s[i]) % q;
		t->h = (r*t->h + t->s[i]) % q;
	}

	for (i = 0; i < (n - m); i++) {
		if (p->h == t->h) {
			if (strings_equal(p->s, t->s, i, p->n)) {
				/* add index where match occurs as an element of linked list */
			}
		}
		if (i < (n - m))
			t->h = (r*(t->h - t->s[i]*high_r) + t->s[i + m]) % q
	}
}
