struct _tree;
struct _node;

#ifdef RED_BLACK_TREE
#define RED_BLACK_TREE
#define BLACK 0
#define RED 1

void rb_insert_fixup(struct _tree *, struct _node *);

#endif /* RED_BLACK_TREE */

#ifndef TRACK_TREE_ALLOCATION
#define TRACK_TREE_ALLOCATION
#define MAX_TREES 16


void dealloc_tree(struct _tree *);

struct tree_entries {
	struct _tree *trees[MAX_TREES];
	int entries;
};

#define INIT_TREE_ENTRIES(name)				\
	struct tree_entries name;			\
	(&name)->entries = 0;				\

#define TREE_ENTRIES_FULL(trees)				\
	((trees)->entries == (MAX_TREES - 1))

#define INSERT_TREE_ENTRY(trees_struct, tree)				\
	do {								\
		typeof(trees_struct) __trees = (trees_struct);		\
		if (!TREE_ENTRIES_FULL(__trees)) {			\
			(__trees)->trees[(__trees)->entries] = tree;	\
			(__trees)->entries += 1;			\
		}							\
	} while(0)

static inline void dealloc_trees(struct tree_entries entries)
{
	int i = 0;
	struct _tree *temp;

	while (i < (&entries)->entries) {
		temp = (&entries)->trees[i];
		printf("second address: %p\n", temp);
		(&entries)->trees[i] = NULL;
		dealloc_tree(temp);
		i++;
	}

}

extern void dealloc_trees(struct tree_entries);
#endif /* TRACK_TREE_ALLOCATION */

#ifndef BST
#define BST

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 98
#endif /* SCREEN_WIDTH */

#ifndef PRINT_DIGITS
#define PRINT_DIGITS 2
#endif /* PRINT_DIGITS */

#ifndef NIL
#define NIL 1
#endif /* NIL */

#ifndef BINARY_SEARCH_TREE_NODE
#define BINARY_SEARCH_TREE_NODE
typedef struct _node {
#ifdef RED_BLACK_TREE
	int color;
#endif /* include extra color attribute for red black trees */
	int nil;
	long key;
	struct _node *p;
	struct _node *left;
	struct _node *right;
	void *obj;
} node;
#endif /* BINARY_SEARCH_TREE_NODE */

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
typedef struct _tree {
	node *root;
	node *nil;
} tree;
#endif /* BINARY_SEARCH_TREE */

void tree_insert(tree*, node*);

int is_nil(node*);
void dealloc_tree_rec(node*);
void dealloc_tree(tree*);
#ifdef TRACK_TREE_ALLOCATION
tree * init_tree(struct tree_entries *);
#else
tree * init_tree(void);
#endif /* TRACK_TREE_ALLOCATION */
node * init_null(void);
node * init_node(tree *, void *, long (*getkey)(void *));

long intgetkey(void*);

tree * construct_tree(long [], const size_t, long (*getkey)(void*), struct tree_entries *);

int parent(int);
int left_child(int);
int right_child(int);

int find_height(node*, int);
int tree_height(tree*);

void print_node_rec(node*);
int two_pow(int);

void add_node_to_array(node*, int, int, long*);

void repeat_char(char, int);

void print_tree(tree*);

node * tree_minimum(node*);
node * tree_maximum(node*);
node * tree_successor(node*);
node * tree_predecessor(node*);

node * tree_search(node *, long k);
void transplant(tree*, node*, node*);

void left_rotate(tree*, node*);
void right_rotate(tree*, node*);

#endif /* BST */
