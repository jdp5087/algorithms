#define RED_BLACK_TREE
#define BLACK 0
#define RED 1

#ifndef BST
#include "bst.h"
#endif /* include bst.h */

void rb_insert(tree*, node*);
void rb_insert_fixup(tree*, node*);
