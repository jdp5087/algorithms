#include <stdlib.h>
#include <stdio.h>

#include "multiplication.h"

int main(int argc, char *argv[])
{
	int i;
	unsigned long key, h;
	
	init_hash_variables(0);

	for (i = 0; i < 31; i++) {
		key = random_unsigned_long();

		h = hash((void *)&key);

		printf("i: %d, key: %lu, hash: %lu\n", i, key, h);

		rebuild_increase(2);
		
	}

	return 0;
}
