#include "Tuple.h"

void swapTuple(Tuple *a, Tuple *b);

void swapTuple(Tuple *a, Tuple *b) {
  Tuple temp = *a;
  *a = *b;
  *b = temp;
}
