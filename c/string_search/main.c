#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "search.h"


int main(int argc, char *argv[])
{
	char line[BUF_LEN];
	FILE *fp;
	printf("%d\n", argc);
	if (argc != 3) {
		printf("Error: invalid number of arguments\n\n"
		       "usage: jrep filename substring\n");
		exit(1);
	}

	if (!(fp = fopen(argv[1], "r"))) {
		printf("Error while opening %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	struct read_status readline_status;
	readline_status.done = 0;

	do {
		readline(line, BUF_LEN, fp, &readline_status);
		printf("%s\n", line);
	} while (!readline_status.done);

	if (fclose(fp) == EOF) {
		printf("Error: %s would not close properly. Info: %s", argv[1], strerror(errno));
		exit(1);
	}
	return 0;
}
