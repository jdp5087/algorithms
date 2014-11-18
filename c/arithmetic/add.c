#define WORD_SIZE 32
#define ALL_BITS (
#define all bits
#define CARRY_BITMASK (1 << 31)

#include <stdio.h>

int needs_carry(unsigned long x, unsigned long y)
{
	//subtract from LONG_MAX in limits.h or whatever it is called
	// then compare to see if next integer is greater than difference
}

unsigned long * add_n(unsigned long *x, unsigned long *y, int n, unsigned long *target)
{
	int i = n - 1;
	int target_i = n + i;
	unsigned long x_i, y_i, c;
	c = 0;
	while (i >= 0) {
		x_i = x[i];
		y_i = y[i];
		target[target_i] = (x_i + y_i + c);
		if ((x_i & CARRY_BITMASK) && (y_i & CARRY_BITMASK))
			c = 1;
		else
			c = 0;
		

		i--;
		target_i--;
	}

// if (c), target[n-1] = 1;
}
