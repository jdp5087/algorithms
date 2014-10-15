#include <stdlib.h>
#include <stdio.h>
#include "search.h"

char buf[BUF_LEN];

int readline(char *line, size_t linesize, FILE *fp)
{
	static int first = 1;
	static int i;
	int j = 0;
	if (first)
		fread((void *)buf, sizeof(char), BUF_LEN, fp);
	first = 0;
	while (buf[i] != '\n') {
		if (j == linesize) {
			printf("Error: line too long for buffer size\n");
			exit(1);
		}
			
		if (buf[i] == EOF) {
			goto eof;
		}
		else if (i == (BUF_LEN - 1)) {
			fread((void *)buf, sizeof(char), BUF_LEN, fp);
			i = 0;
		}
		line[j++] = buf[i++];
	}
	line[j] = '\0';
	i++;
	return j;
	
eof:
	return -1;
}

