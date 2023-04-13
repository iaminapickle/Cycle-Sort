#include "../helper/TupleArr.h"
#include "../helper/Tuple.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void completeCycle(Tuple *arr, int size, int min, int index, int *p);
static int *genCountArray(Tuple *arr, int size, int min, int max);
static void genCumulCountArray(int *count, int min, int max);

// Generates the count array
static int *genCountArray(Tuple *arr, int size, int min, int max) {
  int *count = calloc(max - min + 1, sizeof(*count));
  for (int i = 0; i < size; i++) {
    count[arr[i].n - min]++;
  }
  return count;
}

// Generates cumulative count array
static void genCumulCountArray(int *count, int min, int max) {
  int n1 = count[0];
  int n2 = 0;
  count[0] = 0;
  for (int i = 0; i < max - min + 1; i++) {
    n2 = count[i + 1];
    count[i + 1] = n1 + count[i];
    n1 = n2;
  }
}

void generalCycleSort(TupleArr *tupleArr) {
  Tuple *arr = tupleArr->arr;
  int size = tupleArr->size;
  int max = findMaxValue(arr, 0, size);
  int min = findMinValue(arr, 0, size);

  // Generates count array
  int *count = genCountArray(arr, size, min, max);
  // Generates cumulative count array
  genCumulCountArray(count, min, max);

  for (int i = 0; i < size; i++) {
    // Only complete cycles to previous indices]
    if (i > count[arr[i].n - min]) {
      completeCycle(arr, size, min, i, count);
    }
  }
  free(count);
}

// Rotates an entire cycle once
static void completeCycle(Tuple *arr, int size, int min, int index, int *count) {
  int start = index;
  Tuple cur = arr[index];
  while (true) {
    int pos = count[cur.n - min];
    count[cur.n - min]++;
    swapTuple(&cur, &arr[pos]);

    if (pos == start) {
      return;
    }
  }
}
