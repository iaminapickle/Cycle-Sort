CC = gcc
CFLAGS = -c -Wall
VPATH = ../helper

all: general_cycle_sort.o

general_cycle_sort.o: general_cycle_sort.c
	$(CC) $(CFLAGS) $^

clean:
	rm *.o
