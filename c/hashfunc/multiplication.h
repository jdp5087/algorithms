#define WORD_SIZE 32
#define WORD_MASK 0xFFFFFFFF

struct hash_descriptor {
	unsigned long a;
	unsigned long l;
};

void init_hash_variables(unsigned long modulus);
void rebuild_increase(int multiplier);
void rebuild_decrease(int multiplier);
unsigned long hash(void *key);
unsigned long random_unsigned_long(void);




