#include <stdlib.h>
#include <stdio.h>
#include "string.h"

char *colors[] = {
	ANSI_COLOR_RESET,
	ANSI_COLOR_RED,
	ANSI_COLOR_BLUE,
	ANSI_COLOR_MAGENTA,
	ANSI_COLOR_CYAN,
	ANSI_COLOR_GREEN,
	ANSI_COLOR_YELLOW,
};

/*
  to print a string with all valid offsets highlighted in different colors:

  this construct doesn't require a theta(BUF_SIZE) to initialize our entry array
  (if we just filled it with zeros), instead only theta(valid_offsets)

  -- get the offsets (which we will do with either karp-rabin or knuth-morris-pratt
  -- these will come in a linked list
  -- the stack will be a struct that holds:
       size
       an array of void * that is at least as long as the line we are printing
  -- have another array also at least line length of struct entry holding
      void *
      value
  -- set up by iterating the linked list
      adding entries for each valid offset, where value is set to 1
      adding entries for each valid offset + m, where m is pattern length where value is set to -1
      for each entry, we also add an entry to "stack", which is simply a void * back to the value
  -- iterate string to print
     to discover if current index is in entry array, follow pointer (ONLY IF WITHIN STACK->arr + STACK->size)
           may want to use bitwise ops for efficiency
     if it is, see if stack pointer points back to current entry
     if so, add value to state variable
     if valid entry printf(colors[state]) after adding value to state var
     so if state increases, printf(colors[state]), and if state decreases to 0, printf(colors[state])
          because colors[0] will hold the reset escape sequence


     for each char, putchar() after checking validity and updating state
     now we have a recursive color choosing print statement



       
 */

char buf[BUF_LEN];

/*
  This is necessary because strlen in string.h requires const char *,
  which our strings might not be.
 */
unsigned long stringlength(char *s)
{
	unsigned long n = 0;
	char *sp = s;

	while (*sp != '\0') {
		n++;
		sp++;
	}
	return n;
}

int strings_equal(
	char *first,
	unsigned long first_offset,
	char *second,
	unsigned long second_offset,
	unsigned long length
	)
{
	unsigned long i;
	char *s1, *s2;

	s1 = first + first_offset;
	s2 = second + second_offset;

	for (i = 0; i < length; i++) {
		if (*(s1++) != *(s2++))
			return 0;
	}
	return 1;
	
}

inline void init_print_stack(struct print_stack *stack)
{
	stack->head = stack->arr;
	stack->stop = stack->arr + sizeof(struct entry *)*(BUF_LEN - 1);
}

inline int empty_stack(struct print_stack *stack)
{
	return (stack->head == stack->arr);
}

int add_entry(unsigned long offset, int value, struct entry *entries, struct print_stack *stack)
{
	struct entry *e;
	
	if ((offset < 0) || (offset >= BUF_LEN))
		return -INVALID_OFFSET;
	if (stack->head == stack->stop)
		return -STACK_FULL;

	e = entries + offset;
	stack->head += sizeof(struct entry *);
	e->stack_pointer = stack->head;
	e->value = value;
	*stack->head = e;
	return 0;
}

int is_valid(unsigned long offset, struct entry *entries, struct print_stack *stack)
{
	struct entry *e;
	
	e = entries + offset;
	if ((e->stack_pointer < stack->arr) || (e->stack_pointer > stack->head))
		return 0;
	else if (e == *(e->stack_pointer))
		return 1;
	else
		return 0;
}

inline void reset_stack(struct print_stack *stack)
{
	stack->head = stack->arr;
}


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
	stat->len = j;
	line[j] = '\0';
	i++;
	total++;
	return;
	
}

void print_colored_line(char *line, int lineno, struct entry *entries, struct print_stack *s)
{
	unsigned long i;
	char c = line[0];

	int state = 0;
	printf("line %d: ", lineno);
	for (i = 0; i < BUF_LEN; i++) {
		c = line[i];
		if (c == '\0') {
			if (state)
				printf(colors[0]);
			break;
		}
		if (is_valid(i, entries, s)) {
			state += entries[i].value;
			if ((!state) || (entries[i].value == 1))
				printf(colors[state]);
		}
		putchar(c);
	}
	putchar('\n');
}

/* int main() */
/* { */
/* 	int i; */
/* 	char line[BUF_LEN]; */
/* 	char c = 'A'; */
/* 	for (i = 0; i < 26; i++) { */
/* 		line[i] = c; */
/* 		c++; */
/* 	} */
/* 	line[i] = '\0'; */
	
/* 	struct print_stack stack; */
/* 	struct entry entries[BUF_LEN]; */

/* 	init_print_stack(&stack); */

/* 	add_entry(2, 1, entries, &stack); */
/* 	add_entry(4, -1, entries, &stack); */

/* 	add_entry(10, 1, entries, &stack); */
/* 	add_entry(15, -1, entries, &stack); */

/* 	add_entry(13, 1, entries, &stack); */
/* 	add_entry(18, -1, entries, &stack); */

/* 	print_colored_line(line, 0, entries, &stack); */


/* 	for (i = 0; i < 26; i++) { */
/* 		printf("%d\n", entries[i].value); */
/* 	} */

/* 	return 0; */
	
/* } */
