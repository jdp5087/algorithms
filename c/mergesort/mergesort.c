#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "mergesort.h"

#define ARR_SIZE 100

int mycomp(void *a, void *b)
{
	return (int)(*(unsigned long *)a - *(unsigned long *)b);
}

void merge(void *b, size_t s, int p, int q, int r, int (*cmp)(void *, void *))
{
	void *bp, *lp, *rp, *fp;
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
	lp = L;
	rp = R;
	bp = b + p*s;
	void *lstop = (L + n1*s);
	void *rstop = (R + n2*s);
	for (k = p; k <= r; k++) {
		if (lp == lstop) {
			fp = rp;
			goto finish;
		} else if (rp == rstop) {
			fp = lp;
			goto finish;
		}
		cmp_result = cmp(lp, rp);
		if (cmp_result <= 0) {
			memcpy(bp, lp, s);
			bp += s;
			lp += s;
		} else {
			memcpy(bp, rp, s);
			bp += s;
			rp += s;
		}
	}
finish:
	if (k <= r) {
		memcpy(bp, fp, ((r - k) + 1)*s);
	}
	free(L);
	free(R);
}

void mergesort(void *b, size_t s, int p, int r, int (*cmp)(void *, void *))
{
	int q;
	if (p < r) {
		q = (p+r)/2; /* note that this will truncate, acting as a floor operation */
		mergesort(b, s, p, q, cmp);
		mergesort(b, s, q+1, r, cmp);
		merge(b, s, p, q, r, cmp);
	}
}


int main()
{
	int i;
	srand(time(NULL));
	unsigned long testarr[ARR_SIZE];
	for (i = 0; i < ARR_SIZE; i++) {
		testarr[i] = rand();
	}
	int length = sizeof(testarr)/sizeof(unsigned long);
	void *arr = (void*)&testarr;
	mergesort(arr, sizeof(unsigned long), 0, length, mycomp);
	for (i = 0; i < length; i++)
		printf("%lu, ", testarr[i]);
	printf("\n");
	return 0;
}
