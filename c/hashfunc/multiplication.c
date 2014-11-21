#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "multiplication.h"
#include "../include/sysvars.h"


static struct hash_descriptor desc;

unsigned long random_unsigned_long(void)
{
	return ((unsigned long)rand() << 16) | ((unsigned long)rand());

	
}

unsigned long find_exp_of_power_of_two(unsigned long m)
{
	unsigned long i = 0;
	unsigned long temp = m;
	unsigned long prev_bit = (temp & 1);
	while ((temp >>= 1)) {
		if (temp && prev_bit) {
			printf("Error: given modulus is not a power of two.\n");
			exit(1);
		}
		prev_bit = (temp & 1);
		i++;
	}
	return i;
}

/* modulus must be a power of two!, otherwise the modulus will be reduced to floor(lg(modulus)) */
void init_hash_descriptor(unsigned long modulus)
{
	srand(time(NULL));
	desc.l = find_exp_of_power_of_two(modulus);
	/* This will choose desc.a to be a random odd number between [0x1, 0xFFFFFFFF]  */
	desc.a = random_unsigned_long() | 1;
}


void resize_hash_modulus(unsigned long modulus)
{

	/* It is hard to check for edge cases where the modulus is less than
	   1 or greater than ULONG_MAX because it is likely the result
	   of overflow or underflow. The only value that is certainly
	   wrong is 0, so at least check for that.
	*/
	if (modulus == 0) {
		printf("Did somebody say divide by zero? (RESIZE_HASH_MODULUS)\n");
		exit(1);
	}

	desc.l = find_exp_of_power_of_two(modulus);
}

/*
  See this link (section 2.3) for a really nice proof of the 2-universality of this hash
  function:

  http://www.diku.dk/summer-school-2014/course-material/mikkel-thorup/hash.pdf_copy
 */
unsigned long hash(void *key)
{
	unsigned long k = *(unsigned long *)k;

	printf("desc.l: %lu\n", desc.l);

	if (!desc.l)
		return 0;

	return (desc.a*k) >> (WORD_SIZE - desc.l);
}








/* The following functions have been subbed out
   in favor of one function that just takes a new
   modulus. This way, the hash table has more
   control over resizing
*/





/* multiplier must be a power of two! */
/* void rebuild_increase(int multiplier) */
/* { */
/* 	unsigned long m = find_exp_of_power_of_two(multiplier); */
/* 	if ((desc.l + m) >= WORD_SIZE) { */
/* 		printf("Error: increasing hash function modulus to be greater than %d will cause overflow.", */
/* 		       WORD_SIZE); */
/* 		exit(1); */
/* 	} */
/* 	desc.l += m; */
/* } */

/* multiplier must be a power of two! */
/* void rebuild_decrease(int multiplier) */
/* { */
/* 	if (desc.l < multiplier) { */
/* 		printf("Error: decreasing hash function modulus to be less than 0 does not even make sense," */
/* 		       " just saying."); */
/* 		exit(0); */
/* 	} */
/* } */
