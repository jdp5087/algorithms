struct hash_descriptor {
	unsigned long a;
	unsigned long l;
};

void init_hash_descriptor(unsigned long modulus);
void resize_hash_modulus(unsigned long modulus);
unsigned long hash(void *key);
unsigned long random_unsigned_long(void);




/* void rebuild_increase(int multiplier); */
/* void rebuild_decrease(int multiplier); */


