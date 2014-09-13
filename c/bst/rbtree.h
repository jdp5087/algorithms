#ifdef RED_BLACK_TREE_NEEDED

#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#define BLACK 0
#define RED 1

struct _tree;
struct _node;

void rb_insert(struct _tree*, struct _node*);
void rb_insert_fixup(struct _tree*, struct _node*);

#endif /* RED_BLACK_TREE */

#endif /* RED_BLACK_TREE_NEEDED */
