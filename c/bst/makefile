bst.o: bst.c bst.h
	gcc -c bst.c -o bst.o

rbtree.o: rbtree.c rbtree.h bst.h
	gcc -c rbtree.c - rbtree.o

bst: bst.o
	gcc bst.o -o bst

rbtree: bst.o rbtree.o
	gcc rbtree.o bst.o -o rbtree
