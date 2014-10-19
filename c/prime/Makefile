prime.o: prime.c
	gcc -c prime.c -o prime.o

p: prime.o
	gcc prime.o -o p

dbg.o: prime.c
	gcc -g -c prime.c -o dbg.o

dbg: dbg.o
	gcc dbg.o -o dbg

test: test.c
	gcc test.c -o test -L/usr/include -lm

