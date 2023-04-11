#include "../helper/TupleArr.h"
#include "../helper/Tuple.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void completeCycle(Tuple *arr, int size, int index, int min);

// Special cyclesort algorithm
void specialCycleSort(TupleArr *tupleArr) {
  Tuple *arr = tupleArr->arr;
  int size = tupleArr->size;

  int min = findMinValue(arr, 0, size);
  for (int i = 0; i < size; i++) {
    int j = arr[i].n - min;
    if (i != j) {
      completeCycle(arr, size, i, min);
    }
  }
}

// Rotates an entire cycle once
static void completeCycle(Tuple *arr, int size, int index, int min) {
  int start = index;
  Tuple cur = arr[index];

  while (true) {
    int pos = cur.n - min;

    swapTuple(&cur, &arr[pos]);
    if (pos == start) {
      return;
    }
  }
}
