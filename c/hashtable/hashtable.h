#include "../linked_list/linked_list.h"

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


