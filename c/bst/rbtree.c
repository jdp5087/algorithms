#include "rbtree.h"

void rb_insert(tree *T, node *z)
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


void rb_insert_fixup(tree *T, node *z)
{
	node *y;
	// z is always red, so if z.p is red, we violate rb property
	while (z->p->color == RED) {
		// first three cases
		if (z->p = z->p->p->left) {
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
			} else if (z == z->p->right) { // we can make rotations and quit
				z = z->p;
				left_rotate(T, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			right_rotate(T, z->p->p);
		} else { // second three cases when z = z.p.p.right
			y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
			} else if (z == z->p->left) {
				z = z->p;
				right_rotate(T, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			left_rotate(T, z->p->p);
		}
	}
	// if we inserted a node into an empty tree, the root is red
	// or z.p.p got set to red in case 1 or 4
	T->root->color = BLACK;
}
