#include <stdlib.h>
#include <stdio.h>
#include "search.h"

char buf[BUF_LEN];



void readline(char *line, size_t linesize, FILE *fp, struct read_status *stat)
{
	static int first = 1;
	static int i = 0;
	static int total = 0;
	static int end;
	int j = 0;
	if (first) {
		fseek(fp, 0, SEEK_END);
		end = ftell(fp);
		stat->file_len = end;
		rewind(fp);
		fread((void *)buf, sizeof(char), BUF_LEN, fp);
		}
	first = 0;
	while (buf[i] != '\n') {
		if (total == end) {
			line[j] = '\0';
			stat->len = j;
			stat->done = 1;
			return;
		}
		if (j == linesize) {
			printf("Error: line too long for buffer size\n");
			exit(1);
		}
		if (i > (BUF_LEN - 1)) {
			fread((void *)buf, sizeof(char), BUF_LEN, fp);
			i = 0;
		}
		line[j++] = buf[i++];
		total++;
	}
	line[j] = '\0';
	i++;
	total++;
	return;
	
}

