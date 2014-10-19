#define BUF_LEN (1 << 9) /* 512 Bytes -- small on purpose to make sure buffer reads are working right */

struct read_status {
	int len;
	int done;
	int file_len;
};

void readline(char line[], size_t linesize, FILE *fp, struct read_status *stat);

