#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"


/* to keep things simple, m must always be a power of two.
   
 */

unsigned long power_of_two(unsigned long x)
{
	unsigned long last_bit = (x & 1);
	while ((tmp =>> 1)) {
		if (last_bit)
			return 0;
	}
	return 1;
}

void init_array(struct hashtable *table)
{
	unsigned long i;

	for (i = 0; i < table->m; i++) {
		static_list_init(OFFSET_FROM_POINTER(table->arr, i));
	}
}

void init_hashtable(struct hashtable *table, struct hash_functions *functions,
		    unsigned long size, unsigned long max_load_factor)
{
	table->n = 0;
	if (!power_of_two(size)) {
		printf("Error: %lu is not a power of 2\n");
		exit(1);
	}
	table->m = size;
	table->funcs = functions;
	table->arr = (struct linked_list *)malloc(sizeof(struct linked_list)*size);

	init_array(table);

	
}
