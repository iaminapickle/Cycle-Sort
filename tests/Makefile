CC = gcc
CFLAGS = -c -ggdb -Wall
VPATH = ../src/helper ../src/wiki ../src/general ../src/special

all:
	+$(MAKE) -C ../src/helper
	+$(MAKE) -C ../src/wiki
	+$(MAKE) -C ../src/general
	+$(MAKE) -C ../src/special
	+$(MAKE) tests

tests: tests.c Tuple.o TupleArr.o Algorithm.o AlgorithmArr.o \
			 wiki_cycle_sort.o general_cycle_sort.o special_cycle_sort.o
		$(CC) -g $^ -o tests

Algorithm.o: Algorithm.c
		$(CC) $(CFLAGS) $^

AlgorithmArr.o: AlgorithmArr.c
	 	$(CC) $(CFLAGS) $^

clean:
	+$(MAKE) -C ../src/helper clean
	+$(MAKE) -C ../src/wiki clean
	+$(MAKE) -C ../src/general clean
	+$(MAKE) -C ../src/special clean
	rm *.o
	rm tests
