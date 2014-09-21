
#ifndef BST
#define BST

struct _tree;
struct _node;

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

#ifdef RED_BLACK_TREE
#define TREE_INS(TREE, NODE) rb_insert(TREE, NODE)
#else
#define TREE_INS(TREE, NODE) tree_insert(TREE, NODE)
#endif /* TREE_INS */




int is_nil(node*);
void dealloc_tree_rec(node*);
void dealloc_tree(tree*);


tree * init_tree(void);
node * init_null(void);
node * init_node(tree *, void *, unsigned long (*getkey)(void *));

unsigned long intgetkey(void*);

tree * construct_tree(unsigned long *, const size_t, unsigned long (*getkey)(void*));

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
