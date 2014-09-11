bst.o: bst.c bst.h
	gcc $(DEBUG) -c bst.c -o bst.o

rbtree.o: rbtree.c rbtree.h bst.h
	gcc $(DEBUG) -c rbtree.c -o rbtree.o

main.o: main.c bst.h rbtree.h
	gcc $(DEBUG) -c main.c -o main.o

main: main.o rbtree.o bst.o bst.h rbtree.h
	gcc $(DEBUG) main.o rbtree.o bst.o -o main
