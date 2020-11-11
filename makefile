CC=gcc

INCLUDEPATH=-Iinclude


all: libhashtable.a

libhashtable.a: test.o lnkedlist.o hashtable.o
	ar -rc libhashtable.a lnkedlist.o hashtable.o 

hashtable.o: src/hashtable.c include/lnkedlist.h include/hashtable.h
	$(CC) $(INCLUDEPATH) -c src/hashtable.c

lnkedlist.o: src/lnkedlist.c include/lnkedlist.h
	$(CC) $(INCLUDEPATH) -c src/lnkedlist.c

clean:
	rm *.o
