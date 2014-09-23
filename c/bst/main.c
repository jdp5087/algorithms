#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "bst.h"

// {50, 25, 75, 1, 40, 60, 90}; 
// 



/* void sig_int_handler(int signo) */
/* { */
/* 	if (signo == SIGINT) { */
/* 		if ( */
/* 	} */
		
/* } */

int main()
{
	int i;
	/* wow! an rbtree is guaranteed to have height of no more
	   than 2*lg(n+1) and sure enough, with 1,048,575 RANDOM entries,
	   the tree has height in the mid-30s on average.
	   While mathematically proven, it is still impressive
	   to see it in practice (2*lg(1048575+1) == 40).
	*/


	int n = 255;
	srand(time(NULL));
	long arr[n];
	for (i=0; i<n; i++) {
		arr[i] = (long) rand();
	}
	printf("Got here\n");
	size_t len = (sizeof(arr)/sizeof(long));
	INIT_TREE_ENTRIES(trees)
	tree *T = construct_tree(arr, len, intgetkey, &trees);
	printf("Got here, too!\n");

	/* node *x = tree_maximum(T->root); */
	/* while (!is_nil(x)) { */
	/* 	printf("%ld\n", x->key); */
	/* 	x = tree_predecessor(x); */
//	}
	print_tree(T);
	printf("Got here, finally\n");
	dealloc_trees(trees);
	return 0;
}

