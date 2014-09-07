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
  if (!is_nil(n->left))
    dealloc_tree_rec(n->left);
  if (!is_nil(n->right))
    dealloc_tree_rec(n->right);
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
init_node(tree *T, void *obj, long (*getkey)(void*))
{
  node *n = (node*)malloc(sizeof(node));
  n->nil = 0;
  n->key = getkey(obj);
  n->obj = obj;
  n->left = T->nil;
  n->right = T->nil;
  return n;
}

void
tree_insert(tree *T, node *z)
{
  node *y = T->nil;
  node *x = T->root;
  while (!is_nil(x)) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->p = y;
  if (is_nil(y))
    T->root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
}

long
intgetkey(void *obj)
{

  return *(long*)obj;
}

tree *
construct_tree(const long arr[], const size_t arrlen, long (*getkey)(void*))
{
  int i = 0;
  long current;
  tree *T = init_tree();
  node *n;

  for (i; i < arrlen; i++) {
    current = arr[i];
    n = init_node(T, (void*)&current, getkey);
    tree_insert(T, n);
  }

  return T;
}

int
parent(int i)
{
  return (i/2)-1;
}

int
left_child(int i)
{
  return ((i*2)+1);
}

int
right_child(int i)
{
  return ((i*2)+2);
}

int
find_height(node *n, int height)
{

  if (is_nil(n))
    return height;
  height += 1;
  int left_height = find_height(n->left, height);
  int right_height = find_height(n->right, height);
  if (left_height > right_height)
    return left_height;
  else
    return right_height;
}

int 
tree_height(tree *T)
{

  return find_height(T->root, -1);
}

void print_node_rec(node *n)
{
  if (!is_nil(n)) {

    print_node_rec(n->left);
    print_node_rec(n->right);
  }
}

int
two_pow(x)
{
  return (1 << x);
}

void
add_node_to_array(node *x, int i, int n, long *nodes)
{
  if (i >= n) {
    printf("i must not be greater than n - ADD_NODE_TO_ARRAY\n");
    return;
  }
  if (is_nil(x))
    return;
  nodes[i] = x->key;
  add_node_to_array(x->left, left_child(i), n, nodes);
  add_node_to_array(x->right, right_child(i), n, nodes);
}

void
repeat_char(char c, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    printf("%c", c);
  }
}

void
print_tree(tree *T)
{
  printf("\n");
  int h = tree_height(T);
  if (h > 4) {
    printf("Heights of greater than 4 cannot be formatted correctly. " \
	   "Reducing height to 4 and continuing.\n\n");
    h = 4;
  }
  int n = (two_pow(h+1) - 1);

  int i = 0;
  int j;
  long node_keys[n];
  while (i < n) {
    node_keys[i] = -1;
    i += 1;
  }
  add_node_to_array(T->root, 0, n, node_keys);

  int start;
  int div;
  int offset;
  for (i = 0; i <= h; i++) {
    start = (two_pow(i) - 1);
    div = (two_pow(i) + 1);
    offset = ((SCREEN_WIDTH/div) - (PRINT_DIGITS/2));
    for (j = 0; j < (div - 1); j++) {
      repeat_char(' ', offset);
      if (node_keys[start + j] == -1)
	repeat_char(' ', PRINT_DIGITS);
      else
	printf("%ld", node_keys[start + j]);
    }
    printf("\n\n\n");
  }
  
}
// 
// {50, 25, 75, 99, 1, 40, 60, 55, 57};

int
main()
{
  const long arr[] = {0, 1, 2, 3, 4, 5 ,6};
  size_t len = (sizeof(arr)/sizeof(long));
  tree *T = construct_tree(arr, len, intgetkey);
  print_tree(T);
  dealloc_tree(T);
  return 0;
}
