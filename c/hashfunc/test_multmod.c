#include <gmp.h>
#include <stdio.h>
#include "multmod.h"
#include <time.h>
#include <stdlib.h>

unsigned long random_ui(void)
{
	return (rand() << 16) ^ (rand() << 3) ^ (rand() >> 10);
}

int main(int argc, char *argv[])
{
	int i, k;

	srand(time(NULL));
	
	init_hash_func_descriptor((1 << 31));

	for (i = 0; i < 32; i++) {
		k = random_ui();
		printf("hash: %lu\n", hash((void *)&k));
		printf("hash: %lu\n", hash((void *)&k));

	}

}
