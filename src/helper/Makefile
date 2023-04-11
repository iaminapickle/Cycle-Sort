CC = gcc

CFLAGS = -c -Wall

all: Tuple.o TupleArr.o

Tuple.o: Tuple.c
	$(CC) $(CFLAGS) Tuple.c

TupleArr.o: TupleArr.c Tuple.h
	$(CC) $(CFLAGS) TupleArr.c

clean:
	rm *.o
