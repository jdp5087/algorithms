CC = gcc
LIBS = -lgmp

EXE = hashtable

COMPILE = -c
MACROS = -DHASH_TABLE_LINKED_LIST

OBJECT_PREAMBLE = $(CC) $(COMPILE) $(MACROS)

OBJECTS = linked_list.o multiplication.o hashtable.o test_hashtable.o

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LIBS)

test_hashtable.o : test_hashtable.c hashtable.h ../linked_list/linked_list.h
	$(OBJECT_PREAMBLE) -o test_hashtable.o test_hashtable.c
hashtable.o : hashtable.c hashtable.h ../linked_list/linked_list.h
	$(OBJECT_PREAMBLE) -o hashtable.o hashtable.c
linked_list.o : ../linked_list/linked_list.c ../linked_list/linked_list.h
	$(OBJECT_PREAMBLE) -o linked_list.o ../linked_list/linked_list.c
multiplication.o : ../hashfunc/multiplication.c ../hashfunc/multiplication.h
	$(OBJECT_PREAMBLE) -o multiplication.o ../hashfunc/multiplication.c

clean:
	rm -f $(EXE) $(OBJECTS)
