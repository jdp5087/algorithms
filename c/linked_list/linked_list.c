#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void static_list_init(struct linked_list *x)
{
	x->next = x;
	x->prev = x;
	
}

struct linked_list * list_init(void)
{
	struct linked_list *x;
	x = (struct linked_list *)malloc(sizeof(struct linked_list));
	x->next = x;
	x->prev = x;
	return x;
}

int is_empty(struct linked_list *x)
{
	if (x->next == x && x->prev == x)
		return 1;
	return 0;
}

void list_insert(struct linked_list *x, void *data)
{
	struct linked_list *new, *before;
	new = (struct linked_list *)malloc(sizeof(struct linked_list));
	new->data = data;

	before = x->prev;

	x->prev = new;
	before->next = new;
	new->prev = before;
	new->next = x;
}

void list_delete(struct linked_list *x)
{
	struct linked_list *delete, *before;
	void *data;

	if (!is_empty(x)) {
		delete = x->prev;
		before = delete->prev;
		data = x->prev->data;
		before->next = x;
		x->prev = before;
		free(delete);
		free(data);
	}
	
}

void list_dealloc(struct linked_list *x)
{
	void *data;
	while(!is_empty(x)) {
		list_delete(x);
	}
	free(x);
}

/* int main() */
/* { */
/* 	struct linked_list *a, *e; */
/* 	a = list_init(); */
/* 	void *tmp; */
/* 	int i; */
/* 	for (i = 0; i < 100; i++) { */
/* 		tmp = malloc(sizeof(int)); */
/* 		*(int *)tmp = i; */
/* 		list_insert(a, tmp); */
/* 	} */
/* 	e = a->next; */
/* 	while (e != a) { */
/* 		printf("%d\n", *(int *)e->data); */
/* 		e = e->next; */
/* 	} */

/* 	list_dealloc(a); */

	
/* 	return 0; */
/* } */
