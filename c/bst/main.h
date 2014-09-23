#ifndef TRACK_TREE_ALLOCATION
#define TRACK_TREE_ALLOCATION
#define MAX_TREES 16



struct _tree;
void dealloc_tree(struct _tree *);

struct tree_entries {
	struct _tree *trees[MAX_TREES];
	int entries;
};

extern struct tree_entries total_trees;

INIT_TREE_ENTRIES(total_trees);

#define INIT_TREE_ENTRIES(name)				\
	do {						\
		struct tree_entries name;		\
		(&name)->entries = 0;			\
	} while(0)

#define TREE_ENTRIES_FULL(trees)				\
	(&trees)->entries == (MAX_TREES - 1)


#define INSERT_TREE_ENTRY(trees_struct, tree)					\
	do {								\
		if (!(TREE_ENTRIES_FULL(trees_struct))) {			\
			(&trees_struct)->entries += 1;				\
			(&trees_struct)->trees[(&trees_struct)->entries] = tree;	\
		}							\
	} while(0)

static inline void dealloc_trees(struct tree_entries entries)
{
	int i = 0;
	struct _tree *temp;
	while (i < (&entries)->entries) {
		temp = (&entries)->trees[i];
		(&entries)->trees[i] = NULL;
		dealloc_tree(temp);
		i++;
	}

}



extern void dealloc_trees(struct tree_entries);

#endif /* TRACK_TREE_ALLOCATION */

// #define RED_BLACK_TREE_NEEDED

