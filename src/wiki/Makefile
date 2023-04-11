CC = gcc
CFLAGS = -c -Wall
VPATH = ../helper

all: wiki_cycle_sort.o
	
wiki_cycle_sort.o: wiki_cycle_sort.c
	$(CC) $(CFLAGS) $^

clean:
	rm *.o
