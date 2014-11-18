multiplication.o: multiplication.c multiplication.h
	gcc $(FLAGS) -c multiplication.c -o multiplication.o

test_mult.o: multiplication.o multiplication.h test_mult.c
	gcc $(FLAGS) -c test_mult.c -o test_mult.o

test_mult: multiplication.o test_mult.o
	gcc $(FLAGS) test_mult.o multiplication.o -o test_mult
