#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "search.h"

#define LINE_SIZE (1 << 10)


int main(int argc, char *argv[])
{
	char line[LINE_SIZE];
	if ((argc != 3) && (argc != 4)) {
		printf("Error: invalid number of arguments\n\n"
		       "usage: jrep filename substring\n");
		exit(1);
	}
	FILE *fp;
	if (!(fp = fopen(argv[1], "r"))) {
		printf("Error while opening %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	int q = 0;
	while (readline(line, LINE_SIZE, fp) != -1) {
		printf("%d call to readline\n", q++);
		printf("%s\n", line);
	}
	if (fclose(fp) == EOF) {
		printf("Error: %s would not close properly. Info: %s", argv[1], strerror(errno));
		exit(1);
	}
	return 0;
}
