#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE 32
#define WORD_MASK 0xFFFFFFFF

struct hash_variables {
	unsigned long a;
	unsigned long l;
};

static struct hash_variables vars;

void init_hash_variables(void)
{
	srand(time(NULL));
	vars->l = 0;
	/* This will choose vars->a to be a random odd number between [0x1, 0xFFFFFFFF]  */
	vars->a = (rand() % WORD_MASK) | 1; // This will be truncated to a word anyway...
}

/* multiplier must be a power of two! */
void rebuild_increase(int multiplier)
{
	if ((vars->l + multiplier) >= WORD_SIZE)
		printf("Error: increasing hash function modulus to be greater than %d will cause overflow.",
		       WORD_SIZE);
		exit(1);
	}
	vars->l += multiplier;
}

/* multiplier must be a power of two! */
void rebuild_decrease(int multiplier)
{
	if (vars->l < multiplier) {
		printf("Error: decreasing hash function modulus to be less than 0 does not even make sense,"
		       " just saying.");
		exit(0);
	}
}

/*
  See this link (section 2.3) for a really nice proof of the 2-universality of this hash
  function:

  http://www.diku.dk/summer-school-2014/course-material/mikkel-thorup/hash.pdf_copy
 */
unsigned long hash(void *key)
{
	unsigned long k = *(unsigned long *)k;

	return (vars->a*k) >> (WORD_SIZE - vars->l);
}

