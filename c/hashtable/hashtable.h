struct hash_functions {
	void (*init)(unsigned long);
	void (*resize)(unsigned long);
	unsigned long (*hash)(void *);
};

struct hashtable {
	
};
