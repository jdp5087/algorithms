/* Knuth-Morris-Pratt string matching algorithm.
   See CLRS Chapter 32.4 for more details.*/

#include <stdio.h>

#include "string.h"


void compute_prefixes(char *p, unsigned long m, unsigned long *prefixes)
{
	unsigned long q, k;
	prefixes[0] = 0;
	k = 0;
	for (q = 1; q < m; q++) {
		while ((k > 0) && (p[k] != p[q]))
			k = prefixes[k];
		if (p[k] == p[q])
			k++;
		prefixes[q] = k;
	}

}

void kmp_matcher(char *t, unsigned long n, char *p, unsigned long m,
		 struct entry *entries, struct print_stack *stack, unsigned long *prefixes)
{
	unsigned long i, q;

	q = 0;

	for (i = 0; i < n; i++) {
		while ((q > 0) && (p[q] != t[i]))
			q = prefixes[q];
		if (p[q] == t[i])
			q++;
		if (q == m) {
			add_entry((i - (m - 1)), 1, entries, stack);
			add_entry((i + 1), -1, entries, stack);
			q = prefixes[q];
		}
			
	}
	
}
	

void kmp(FILE *fp, char *p)
{
	unsigned long m;
	
	struct read_status stat;
	m = stringlength(p);

	unsigned long prefixes[m];


	char line[BUF_LEN];
	struct print_stack stack;
	struct entry entries[BUF_LEN];
	init_print_stack(&stack);

	int lineno = 0;
	stat.done = 0;


	compute_prefixes(p, m, prefixes);

	do {
		readline(line, BUF_LEN, fp, &stat);
		if (stat.len >= m)
			kmp_matcher(line, stat.len, p, m, entries, &stack, prefixes);
		if (!empty_stack(&stack)) {
			print_colored_line(line, lineno, entries, &stack);
			reset_stack(&stack);
		}
		lineno++;
	} while (!stat.done);
}


