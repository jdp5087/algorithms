#include "../linked_list/linked_list.h"
#include <limits.h>

#define WILL_OVERFLOW(x, multiplicand) ((x) > ((ULONG_MAX)/multiplicand))
#define LOAD_FACTOR(table) ((table->n)/(table->m))
#define INCREASE_FACTOR 2
#define DECREASE_FACTOR 4


struct hash_functions {
	void (*init)(unsigned long);
	void (*resize)(unsigned long);
	unsigned long (*hash)(void *);
};

struct hashtable {
	unsigned long n, m, load;
	struct linked_list *arr;
	struct hash_functions *funcs;
};

#define OFFSET_FROM_POINTER(p, n) ((p) + sizeof((p))*(n))

#define INIT_HASH_FUNCTIONS(f, initialize, resize_modulus, hash_function) \
	do {								\
		typeof(f) tmp = f;					\
		tmp->init = initialize;					\
		tmp->resize = resize_modulus;				\
		tmp->hash = hash_function;				\
	} while (0);

void init_hashtable(struct hashtable *table, struct hash_functions *functions,
		    unsigned long size, unsigned long max_load_factor);



