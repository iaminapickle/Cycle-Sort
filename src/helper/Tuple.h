#ifndef TUPLE_H
#define TUPLE_H

typedef struct tuple_struct {
  int n;
  char c;
} Tuple;

void swapTuple(Tuple *a, Tuple *b);

#endif
