struct _tree;
struct _node;

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 80
#endif /* SCREEN_WIDTH */

#ifndef NIL
#define NIL 1
#endif /* NIL */

#ifndef BINARY_SEARCH_TREE_NODE
#define BINARY_SEARCH_TREE_NODE

typedef struct _node {
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

tree * init_tree(void);
node * init_null(void);
node * init_node(void *, long (*getkey)(void *));

