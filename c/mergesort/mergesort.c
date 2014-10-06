#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "mergesort.h"

/* long pass_through(void *) */

/* void merge(void *A[], long (*getkey)(void*), unsigned long p, unsigned long q, unsigned long r) */
/* { */
/* 	printf("%ul\n", A[2]); */
/* } */

int mycomp(void *a, void*b)
{
	return (int)(*(unsigned long *)a - *(unsigned long *)b);
}

void merge(void *b, size_t s, int p, int q, int r, int (*cmp)(void *, void *))
{
	void *lp, *rp, *fp;
	int n1 = (q - p + 1);
	int n2 = (r - q);
	int k, cmp_result;
	void *L = malloc(s*n1);
	if (L == NULL) {
		printf("Allocation of %d bytes for L array failed.\n", n1);
		exit(1);
	}
	void *R = malloc(s*n2);
	if (R == NULL) {
		printf("Allocation of %d bytes for R array failed.\n", n2);
		exit(1);
	}
	memcpy(L, b + p*s, n1*s); /* move n1*s bytes from b + p to temp array L */
	memcpy(R, b + (q + 1)*s, n2*s); /* move n2*s bytes from b + q + 1 to temp array R */
	void *lstop = (L + (n1 - 1)*s);
	void *rstop = (R + (n2 - 1)*s);
	for (k = p; k <= r; k++) {
		if (lp == lstop) {
			fp = rp;
			goto finish;
		} else if (rp == rstop) {
			fp = lp;
			goto finish;
		}
		cmp_result = cmp(lp, rp);
		if (cmp_result >= 0) {
			memcpy(b + k*s, lp, s);
			lp += s;
		} else {
			memcpy(b + k*s, rp, s);
			rp += s;
		}
	}
finish:
	while (k <= r) {
		memcpy(b + k*s, fp, s);
		fp += s;
		k++;
	}
	free(L);
	free(R);
}


int main()
{
	int i;
	unsigned long testarr[] = {9,8,7,6,5,4,3,2,1,0};
	int length = sizeof(testarr)/sizeof(unsigned long);
	void *arr = (void*)&testarr;
	merge(arr, sizeof(unsigned long), 0, 4, 9, mycomp);
	for (i = 0; i < length; i++)
		printf("lu\n", testarr[i]);
	return 0;
}
/* include a size (of object) and length parameter in merge sort, this way, pointer arithmetic will be suffiecient
   to manipulate the array.
   This will be challenging, but a worthwhile exercise
*/
