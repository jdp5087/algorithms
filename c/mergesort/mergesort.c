#include <stdio.h>
#include "mergesort.h"

/* long pass_through(void *) */

/* void merge(void *A[], long (*getkey)(void*), unsigned long p, unsigned long q, unsigned long r) */
/* { */
/* 	printf("%ul\n", A[2]); */
/* } */



int main()
{
	/* unsigned long myvar = 20; */
	/* void *test = (void*)&myvar; */
	/* printf("%ul\n", *(unsigned long *)test); */
	/* printf("size of unsigned long %d, size of void *: %d\n", */
	/*        sizeof(unsigned long), sizeof(void *)); */
	unsigned long testarr[] = {0,1,2,3,4,5,6,7,8};
	int length = sizeof(testarr)/sizeof(unsigned long);
	void *arr = (void*)&testarr;
	int i;
	for (i = 0; i < length; i++) {
		printf("%d\n", ((unsigned long*)arr)[i]);
	}
	return 0;
}
/* include a size (of object) and length parameter in merge sort, this way, pointer arithmetic will be suffiecient
   to manipulate the array.
   This will be challenging, but a worthwhile exercise
*/
