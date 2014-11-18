struct linked_list {
	struct linked_list *prev;
	struct linked_list *next;
#ifdef HASH_TABLE_LINKED_LIST
	void *key;
#endif
	void *data;
};

struct linked_list * list_init(void);
int is_empty(struct linked_list *x);
void list_insert(struct linked_list *x, void *data);
void list_delete(struct linked_list *x);
void list_dealloc(struct linked_list *x);
