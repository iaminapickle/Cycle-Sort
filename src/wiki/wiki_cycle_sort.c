#include "../helper/TupleArr.h"
#include "../helper/Tuple.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int findNoSmaller(Tuple *arr, int size, int n);
static int findNoCopiesBefore(Tuple *arr, int size, int n, int end);
static void completeCycle(Tuple *arr, int size, int index);
static bool checkCorrectPos(Tuple *arr, int size, int index);

// Finds the number of elements with values smaller than n
static int findNoSmaller(Tuple *arr, int size, int n) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i].n < n) {
      sum += 1;
    }
  }
  return sum;
}

// Finds the number of elements with values equal to n before a certain index
static int findNoCopiesBefore(Tuple *arr, int size, int n, int end) {
  int sum = 0;
  for (int i = 0; i < end; i++) {
    if (arr[i].n == n) {
      sum += 1;
    }
  }
  return sum;
}

void wikiCycleSort(TupleArr *tupleArr) {
  Tuple* arr = tupleArr->arr;
  int size = tupleArr->size;

  for (int i = 0; i < size; i++) {
    // If an element is not in it's correct position
    if (!checkCorrectPos(arr, size, i)) {
      // Rotate every element in its cycle once
      completeCycle(arr, size, i);
    }
  }
}

// Checks if the given index contains the correct value
static bool checkCorrectPos(Tuple *arr, int size, int index) {
  int noSmaller = findNoSmaller(arr, size, arr[index].n);
  int noCopies = findNoCopiesBefore(arr, size, arr[index].n, index);

  return (index == noSmaller + noCopies);
}

// Rotates an entire cycle once
static void completeCycle(Tuple *arr, int size, int index) {
  int i = index;
  int start = i;
  Tuple cur = arr[i];

  while (true) {
    // The index it is supposed to go to
    int pos = findNoSmaller(arr, size, cur.n);
    // Since we never change the value of arr[start], we must account for it
    if (arr[start].n < cur.n) {
      pos -= 1;
    }

    // If pos does not contain a cur value (no duplicate)
    if (arr[pos].n != cur.n) {
      swapTuple(&cur, &arr[pos]);
      i = pos;
    } else {
      // If pos does contain a cur value (duplicate value)
      // Swap with next available value
      for (int j = pos + 1; j < size; j++) {
        if (arr[j].n != cur.n) {
          swapTuple(&cur, &arr[j]);
          i = j;
          break;
        }
      }
    }

    // If we have looped back to the start
    if (i == start) {
      break;
    }
  }
}
