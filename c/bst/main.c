#include <stdlib.h>
#include <stdio.h>

#include "rbtree.h"

// {50, 25, 75, 1, 40, 60, 90}; 
// 
int main()
{
	const long arr[] = {0, 1, 2, 3, 4, 5 ,6};
	size_t len = (sizeof(arr)/sizeof(long));
	tree *T = construct_tree(arr, len, intgetkey);
	node *x = tree_maximum(T->root);
	while (!is_nil(x)) {
		printf("%ld\n", x->key);
		x = tree_predecessor(x);
	}
	print_tree(T);
	dealloc_tree(T);
	return 0;
}

