#define BUF_LEN (1 << 9) /* 512 Bytes -- small on purpose to make sure buffer reads are working right */

int readline(char line[], size_t linesize, FILE *fp);	

