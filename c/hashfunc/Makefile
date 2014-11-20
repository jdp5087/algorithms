CC = gcc
LIBS = -lgmp

objects_mult = multiplication.o test_mult.o
objects_multmod = multmod.o test_multmod.o

test_multmod : $(objects_multmod)
	$(CC) -o test_multmod $(objects_multmod) $(LIBS)

test_mult : $(objects_mult)
	$(CC) -o test_mult $(objects_mult)

multiplication.o: multiplication.h
test_mult.o: multiplication.h multiplication.c
multmod.o: multmod.h multmod.c
	$(CC) -c -o multmod.o multmod.c
test_multmod.o: test_multmod.c multmod.h multmod.c
	$(CC) -c -o test_multmod.o test_multmod.c

.PHONY: clean
clean:
	rm test_multmod test_mult $(objects_multmod) $(objects_mult)





# multiplication.o: multiplication.c multiplication.h
# 	gcc $(FLAGS) -c multiplication.c -o multiplication.o

# test_mult.o: multiplication.o multiplication.h test_mult.c
# 	gcc $(FLAGS) -c test_mult.c -o test_mult.o

# test_mult: multiplication.o test_mult.o
# 	gcc $(FLAGS) test_mult.o multiplication.o -o test_mult

# multmod.o: multmod.c multmod.h
# 	gcc $(FLAGS) -c multmod.c -o multmod.o

# test_multmod.o: test_multmod.c multmod.c multmod.h
# 	gcc $(FLAGS) -c test_multmod.c -o test_multmod.o

# test_multmod: multmod.o test_multmod.o
# 	gcc $(FLAGS) multmod.o test_multmod.o -o test_multmod
