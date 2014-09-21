#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "rbtree.h"
#include "bst.h"

// {50, 25, 75, 1, 40, 60, 90}; 
// 
int main()
{
	int i;
	/* wow! an rbtree is guaranteed to have height of no more
	   than 2*lg(n+1) and sure enough, with 1,048,575 RANDOM entries,
	   the tree has height in the mid-30s on average.
	   While mathematically proven, it is still impressive
	   to see it in practice (2*lg(1048575+1) == 40).
	*/
	int n = 1048575;
	srand(time(NULL));
	unsigned long arr[n];
	printf("size: %d\n", sizeof(&arr));
	for (i=0; i<n; i++) {
		arr[i] = (unsigned long) rand();
	}

	size_t len = (sizeof(arr)/sizeof(unsigned long));
	printf("Size of array: %d\n", len);
	printf("size of array: %d\n", sizeof(arr));
	printf("Starts at: %p, ends at: %p\n", &arr, ((void*)(unsigned long)&arr + sizeof(arr)));
	tree *T = construct_tree((unsigned long *)&arr, len, intgetkey);

	
	/* node *x = tree_maximum(T->root); */
	/* while (!is_nil(x)) { */
	/* 	printf("%ld\n", x->key); */
	/* 	x = tree_predecessor(x); */
//	}
	print_tree(T);
	printf("Got here, finally\n");
	dealloc_tree(T);
	return 0;
}

