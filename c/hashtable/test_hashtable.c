#include <stdio.h>

#include "hashtable.h"
#include "../hashfunc/multiplication.h"

int main(int argc, char *argv[])
{
	struct hash_functions funcs;
	struct hashtable table;

	INIT_HASH_FUNCTIONS(&funcs, init_hash_descriptor,
			    resize_hash_modulus, hash);

	init_hashtable(&table, &funcs, 1, 2);

	

}
