search.o: search.c search.h
	gcc -c search.c -o search.o

main.o: main.c search.c search.h
	gcc -c main.c -o main.o

jrep: main.o search.o
	gcc search.o main.o -o jrep

dsearch.o: search.c search.h
	gcc -g -c search.c -o dsearch.o

dmain.o: main.c search.c search.h
	gcc -g -c main.c -o dmain.o

dbg: dmain.o dsearch.o
	gcc -g dsearch.o dmain.o -o dbg
