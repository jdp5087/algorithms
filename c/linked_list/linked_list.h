struct linked_list {
	struct linked_list *prev;
	struct linked_list *next;
#ifdef HASH_TABLE_LINKED_LIST
	void *key;
#endif
	void *data;
};

void static_list_init(struct linked_list *x);
struct linked_list * list_init(void);

int is_empty(struct linked_list *x);

void list_delete(struct linked_list *x);
void static_list_dealloc(struct linked_list *x);
void list_dealloc(struct linked_list *x);


#ifdef HASH_TABLE_LINKED_LIST
void list_insert(struct linked_list *x, void *key, void *data);
#endif /* HASH_TABLE_LINKED_LIST */

#define LINKED_LIST_LOOP(head, e)			\
	for (e = head->next; e != head; e = e->next)
	
