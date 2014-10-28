FORCE:

search.o: search.c search.h FORCE
	gcc $(FLAGS) -c search.c -o search.o


../prime/prime.o: ../prime/prime.c ../prime/prime.h FORCE
	gcc $(FLAGS) -c ../prime/prime.c -o ../prime/prime.o

karp_rabin.o: ../prime/prime.h search.h karp_rabin.c karp_rabin.h FORCE
	gcc $(FLAGS) -c karp_rabin.c -o karp_rabin.o

main.o: main.c search.h ../prime/prime.h karp_rabin.h FORCE
	gcc $(FLAGS) -c main.c -o main.o

jrep: search.o ../prime/prime.o karp_rabin.o main.o FORCE
	gcc $(FLAGS) ../prime/prime.o search.o karp_rabin.o main.o -o jrep
