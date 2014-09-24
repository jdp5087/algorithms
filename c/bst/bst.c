#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "bst.h"


int is_nil(node *n)
{
	return n->nil;
}

void dealloc_tree_rec(node *n)
{
	if (!is_nil(n->left))
		dealloc_tree_rec(n->left);
	if (!is_nil(n->right))
		dealloc_tree_rec(n->right);
	free(n);

}

void dealloc_tree(tree *T)
{
	if (!is_nil(T->root))
		dealloc_tree_rec(T->root);
	free(T->nil);
	free(T);
}

#ifdef TRACK_TREE_ALLOCATION
tree * init_tree(struct tree_entries *trees)
#else
tree * init_tree(void)
#endif /* TRACK_TREE_ALLOCATION */
{
	tree *T = (tree*)malloc(sizeof(tree));
#ifdef TRACK_TREE_ALLOCATION
	INSERT_TREE_ENTRY(trees, T);
#endif /* TRACK_TREE_ALLOCATION */
	node *n = init_null();
	T->nil = n;
	T->root = T->nil;
	return T;
}

node * init_null(void)
{
	node *n = (node*)malloc(sizeof(node));
	n->nil = 1;
#ifdef RED_BLACK_TREE
	n->color = BLACK;
#endif /* set color to black on T.nil */
	return n;
}

node * init_node(tree *T, void *obj, long (*getkey)(void*))
{
	node *n = (node*)malloc(sizeof(node));
	n->nil = 0;
	n->key = getkey(obj);
	n->obj = obj;
	n->left = T->nil;
	n->right = T->nil;
#ifdef RED_BLACK_TREE
	n->color = RED;
#endif
	return n;
}

#ifdef RED_BLACK_TREE
void tree_insert(tree *T, node *z)
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
	if (y == T->nil)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	rb_insert_fixup(T, z);
}

void rb_insert_fixup(struct _tree *T, struct _node *z)
{
	node *y;
	// z is always red, so if z.p is red, we violate rb property
	while (z->p->color == RED) {
		// first three cases
		if (z->p == z->p->p->left) {
			// z's uncle
			y = z->p->p->right;
			// we can't rotate and quit without changing
			// black height of z, so we change
			// z.p and z's uncle to black and move
			// the red to z.p.p
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				if (z == z->p->right) { // we can make rotations and quit
					z = z->p;
					left_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(T, z->p->p);
			}
		} else { // second three cases when z = z.p.p.right
			
			y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				if (z == z->p->left) {
					z = z->p;
					right_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(T, z->p->p);
			}
		}
	}
	// if we inserted a node into an empty tree, the root is red
	// or z.p.p got set to red in case 1 or 4
	T->root->color = BLACK;
}

#else



void tree_insert(tree *T, node *z)
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

void tree_delete(tree *T, node *z)
{
	if (is_nil(z->left)) {
		transplant(T, z, z->right);
	}
	else if (is_nil(z->right)) {
		transplant(T, z, z->left);
	}
	else {
		node *y = tree_minimum(z->right);
		if (y->p != z) {
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		
		y->left->p = y;
	}
}

#endif /* RED_BLACK_TREE */

long intgetkey(void *obj)
{
	return *(long*)obj;
}


int parent(int i)
{
	return (i/2)-1;
}

int left_child(int i)
{
	return ((i*2)+1);
}

int right_child(int i)
{
	return ((i*2)+2);
}

int find_height(node *n, int height)
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

int tree_height(tree *T)
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

int two_pow(int x)
{
	return (1 << x);
}

void add_node_to_array(node *x, int i, int n, long *nodes)
{
	if (i >= n) {
		return;
	}
	if (is_nil(x))
		return;
	nodes[i] = x->key;
	add_node_to_array(x->left, left_child(i), n, nodes);
	add_node_to_array(x->right, right_child(i), n, nodes);
}

void repeat_char(char c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%c", c);
	}
}

void print_tree(tree *T)
{
	printf("\n");
	int h = tree_height(T);
	printf("height: %d\n", h);
	if (h > 4) {
		printf("Heights of greater than 4 cannot be formatted correctly. " \
		       "Reducing height to 4 and continuing.\n\n");
		h = 4;
	}
	int i = 0;
	int j;
	int n = (two_pow(h+1) - 1);
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

void transplant(tree *T, node *u, node *v)
{
	if (is_nil(u->p))
		T->root = v;
	else if (u = u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (!is_nil(v))
		v->p = u->p;
}

node * tree_minimum(node *x)
{
	while (!is_nil(x->left)) {
		x = x->left;
	}
	return x;
}

node * tree_maximum(node *x)
{
	while (!is_nil(x->right)) {
		x = x->right;
	}
	return x;
}

node * tree_successor(node *x)
{
	if (!is_nil(x->right))
		return tree_minimum(x->right);
	node *y = x->p;
	while (!is_nil(y) && (y->right == x)) {
		x = y;
		y = y->p;
	}
	return y;
}

node * tree_predecessor(node *x)
{
	if (!is_nil(x->left))
		return tree_maximum(x->left);
	node *y = x->p;
	while (!is_nil(y) && (y->left == x)) {
		x = y;
		y = y->p;
	}
	return y;
}


node * tree_search(node *x, long k)
{
	while ((!is_nil(x)) && (k != x->key)) {
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}


void left_rotate(tree *T, node *x)
{
	node *y = x->right;
	x->right = y->left;
	if (!is_nil(y->left))
		y->left->p = x;
	y->p = x->p;
	if (is_nil(x->p))
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void right_rotate(tree *T, node *x)
{
	node *y = x->left;
	x->left = y->right;
	if (!is_nil(y->right))
		y->right->p = x;
	y->p = x->p;
	if (is_nil(x->p))
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->right = x;
	x->p = y;
}

tree * construct_tree(long arr[], const size_t arrlen, long (*getkey)(void*), struct tree_entries *trees)
{
	int i = 0;
	long current;
	tree *T = init_tree(trees);
	printf("first address: %p\n", T);
	node *n;
	for (i; i < arrlen; i++) {
		current = arr[i];
		n = init_node(T, (void*)&current, getkey);
		tree_insert(T, n);
	}
	return T;
}
