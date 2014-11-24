#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"


/* to keep things simple, m must always be a power of two.
   
 */

unsigned long power_of_two(unsigned long x)
{
	unsigned long last_bit = (x & 1);
	while ((x >>= 1)) {
		if (last_bit)
			return 0;
		last_bit = (x & 1);
	}
	return 1;
}

void init_array(struct hashtable *table)
{
	unsigned long i;

	for (i = 0; i < table->m; i++)
		static_list_init(OFFSET_FROM_POINTER(table->arr, i));
}

void dealloc_hashtable(struct hashtable *table)
{
	struct linked_list *tmp;

	
}

void rehash_old_array(struct hashtable *table, struct linked_list *old_arr,
		       unsigned long old_size)
{
	unsigned long i;
	struct linked_list *entry;
	for (i = 0; i < old_size; i++) {
		LINKED_LIST_LOOP(OFFSET_FROM_POINTER(old_arr, i), entry) {
			list_insert(OFFSET_FROM_POINTER(table->arr, table->funcs->hash(entry->key)),
				    entry->key,
				    entry->data);
							
		}
		
	}

}


/* resize both table and hash function, rehash_old_array */
void resize_table(struct hashtable *table, unsigned long size)
{
	struct linked_list *old_arr;
	unsigned long old_size;

	old_size = table->m;
	table->m = size;
	table->funcs->resize(size);

	old_arr = table->arr;
	table->arr = (struct linked_list *)malloc(sizeof(struct linked_list)*size);
	init_array(table);

	rehash_old_array(table, old_arr, old_size);

	free(old_arr);
}

		       


void init_hashtable(struct hashtable *table, struct hash_functions *functions,
		    unsigned long size, unsigned long max_load_factor)
{
	table->n = 0;
	if (!power_of_two(size)) {
		printf("Error: %lu is not a power of 2\n", size);
		exit(1);
	}
	table->m = size;
	table->funcs = functions;
	table->arr = (struct linked_list *)malloc(sizeof(struct linked_list)*size);
	table->load = max_load_factor;

	init_array(table);
}

/* Now I am starting to regret using void * for keys, because now
   every entry must also have a pointer to the key, meaning that 
   space is used for both a pointer and whatever the key is. It is also
   mildly incovenient because every key must be saved in memory: they must be
   dynamically allocated and then freed. That being said, onward was the cry.
   
 */

/* check clrs, but it seems that care should be taken
   on insert, because if a key already exists and the policy is to overwrite,
   then it would be better to check to see if the key is already in the table.
   if so, then just overwrite and return. If not, then check if a resize is necessary,
   and then do insert. This sounds tricky and overly annoying.

   Another alternative would be to just do the insert, which will overwrite
   if key is already in table. then increment table->n, and only after that check
   the load factor to see if a resize is necessary. With this route, the first action
   in the function should probably check the LOAD_FACTOR(table), because without
   this check it will just insert into the table indefinitely if the table is already
   at max size (can't resize upwards, but still makes the insert).
   
   

   A LOAD_FACTOR(table) macro might be useful!
*/
void insert(struct hashtable *table, void * key, void *data)
{
	if (((table->n + 1)/table->m) >= table->load) {
		if (WILL_OVERFLOW(table->m, INCREASE_FACTOR)) {
			printf("Cannot insert another element, table is already at max size and "
			       "load factor. Size: %lu slots, load_factor: %lu.\n",
			       table->m, table->load);
			return;
		}

		
		resize_table(table, table->m*INCREASE_FACTOR);
	}

	


	
}
