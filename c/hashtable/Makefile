CC = gcc
LIBS = -lgmp

EXE = hashtable

LINKED_LIST_MACROS = -DHASH_TABLE_LINKED_LIST

objects = test_hashtable.o hashtable.o linked_list.o multiplication.o

$(EXE) : $(objects)
	$(CC) -o $(EXE) $(objects)

test_hashtable.o : hashtable.h ../linked_list/linked_list.h
hashtable.o : hashtable.h ../linked_list/linked_list.h
linked_list.o : ../linked_list/linked_list.c ../linked_list/linked_list.h
	$(CC) $(LINKED_LIST_MACROS) -o linked_list.o ../linked_list/linked_list.c
multiplication.o : ../hashfunc/multiplication.c ../hashfunc/multiplication.h
	$(CC) -o multiplication.o ../hashfunc/multiplication.c

clean:
	rm -f $(EXE) $(objects)
