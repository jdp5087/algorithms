#ifndef SEARCH_HEADER
#define SEARCH_HEADER

#define BUF_LEN (1 << 10) /* 512 Bytes -- small on purpose to make sure buffer reads are working right */

#define INVALID_OFFSET 1
#define STACK_FULL 2

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"



extern char *colors[];

struct print_stack {
	struct entry **head;
	struct entry *arr[BUF_LEN];
	struct entry **stop;
};

struct entry {
	struct entry **stack_pointer;
	int value;
};

struct read_status {
	int len;
	int done;
	int file_len;
};

unsigned long stringlength(char *s);
int strings_equal(
	char *first,
	unsigned long first_offset,
	char *second,
	unsigned long second_offset,
	unsigned long length
	);


inline void init_print_stack(struct print_stack *stack);
inline int empty_stack(struct print_stack *stack);
int add_entry(unsigned long offset, int value, struct entry *entries, struct print_stack *stack);
inline void reset_stack(struct print_stack *stack);
void readline(char line[], size_t linesize, FILE *fp, struct read_status *stat);
void print_colored_line(char *line, int lineno, struct entry *entries, struct print_stack *s);

#endif /* SEARCH_HEADER */

