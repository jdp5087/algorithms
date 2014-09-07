#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

int
is_nil(node *n)
{
  return n->nil;
}

void
dealloc_tree_rec(node *n)
{
  if (!is_nil(n->left)) {
    dealloc_tree_rec(n->left);
  } else if (!is_nil(n->right)) {
    dealloc_tree_rec(n->right);
  }
  free(n);
}

void 
dealloc_tree(tree *T)
{
  if (!is_nil(T->root))
    dealloc_tree_rec(T->root);
  free(T->nil);
  free(T);
}

tree *
init_tree(void)
{
  tree *T = (tree*)malloc(sizeof(tree));
  node *n = init_null();
  T->nil = n;
  T->root = T->nil;
  return T;
}

node *
init_null(void)
{
  node *n = (node*)malloc(sizeof(node));
  n->nil = 1;
  return n;
}

node *
init_node(void *obj, long (*getkey)(void*))
{
  node *n = (node*)malloc(sizeof(node));
  n->nil = 0;
  n->key = getkey(obj);
  n->obj = obj;
  return n;
}




int
main()
{
  tree *T = init_tree();
  dealloc_tree(T);
  return 0;
}
