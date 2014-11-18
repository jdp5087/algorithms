FORCE:

string.o: string.c string.h FORCE
	gcc $(FLAGS) -c string.c -o string.o


../prime/prime.o: ../prime/prime.c ../prime/prime.h FORCE
	gcc $(FLAGS) -c ../prime/prime.c -o ../prime/prime.o

karp_rabin.o: ../prime/prime.h string.h karp_rabin.c karp_rabin.h FORCE
	gcc $(FLAGS) -c karp_rabin.c -o karp_rabin.o

jmain.o: main.c string.h ../prime/prime.h karp_rabin.h FORCE
	gcc $(FLAGS) -c main.c -o main.o

kmpmain.o: main.c string.h kmp.h
	gcc $(FLAGS) -c main.c -o kmpmain.o

jrep: string.o ../prime/prime.o karp_rabin.o main.o FORCE
	gcc $(FLAGS) ../prime/prime.o string.o karp_rabin.o main.o -o jrep

kmprep: string.o kmp.o kmpmain.o
	gcc $(FLAGS) string.o kmp.o kmpmain.o -o kmprep
