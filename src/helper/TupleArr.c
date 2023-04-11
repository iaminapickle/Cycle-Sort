#include "TupleArr.h"
#include "Tuple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

TupleArr *initTupleArr(int size) {
  TupleArr *tupleArr = malloc(sizeof(*tupleArr));
  tupleArr->size = size;
  tupleArr->arr = malloc(size * sizeof(*tupleArr->arr));

  return tupleArr;
}

TupleArr *genRandomTupleArr(int size, int max, int seed) {
  TupleArr *tupleArr = initTupleArr(size);

  randomiseTuples(tupleArr, max, seed);
  return tupleArr;
}

void randomiseTuples(TupleArr *tupleArr, int max, int seed) {
  srand(seed);

  int count[max + 1];
  memset(count, 0, sizeof(count));
  for (int i = 0; i < tupleArr->size; i++) {
    int num = rand() % (max + 1);
    tupleArr->arr[i].n = num;
    tupleArr->arr[i].c = count[num] + 97;
    count[num]++;
  }
}

void randomiseTuples_Cons(TupleArr *tupleArr, int seed) {
  srand(seed);

  int num = rand() % (RAND_MAX - tupleArr->size + 1);

  for (int i = 0; i < tupleArr->size; i++) {
    tupleArr->arr[i].n = num + i;
    tupleArr->arr[i].c = 97;
  }
  shuffleTupleArr(tupleArr);
}

void randomiseTuples_Max(TupleArr *tupleArr, int max, int seed) {
  srand(seed);

  tupleArr->arr[0].n = 0;
  tupleArr->arr[1].n = max;
  for (int i = 2; i < tupleArr->size; i++) {
    int num = rand() % (max + 1);
    tupleArr->arr[i].n = num;
  }

  shuffleTupleArr(tupleArr);

  int count[max + 1];
  memset(count, 0, sizeof(count));
  for (int i = 0; i < tupleArr->size; i++) {
    int num = tupleArr->arr[i].n;
    tupleArr->arr[i].c = count[num] + 97;
    count[num]++;
  }
}

// n_unique <= size
void randomiseTuples_Unique(TupleArr *tupleArr, int max, int n_unique, int seed) {
  srand(seed);

  if (n_unique == tupleArr->size) {
      for (int i = 0; i < tupleArr->size; i++) {
        tupleArr->arr[i].n = i;
        tupleArr->arr[i].c = 'a';
      }
      shuffleTupleArr(tupleArr);
      return;
  }

  int values[n_unique];
  for (int i = 0; i < n_unique; i++) {
    int flag;
    int num = 0;
    do {
      num = rand() % (max + 1);
      flag = 0;
      for (int j = 0; j < i; j++) {
        if (values[j] == num) {
          flag = 1;
        }
      }
    } while (flag == 1);
    values[i] =  num;
  }

  int count[max + 1];
  memset(count, 0, sizeof(count));
  for (int i = 0; i < n_unique; i++) {
    tupleArr->arr[i].n = values[i];
  }

  for (int i = n_unique; i < tupleArr->size; i++) {
    int val = values[rand() % n_unique];
    tupleArr->arr[i].n = val;
  }
  shuffleTupleArr(tupleArr);

  for (int i = 0; i < tupleArr->size; i++) {
    tupleArr->arr[i].c = count[tupleArr->arr[i].n] + 97;
    count[tupleArr->arr[i].n]++;
  }
}

void shuffleTupleArr(TupleArr *tupleArr) {
  Tuple *arr = tupleArr->arr;

  int j = tupleArr->size - 1;
  for (int i = 0; i < j; i++) {
    int index = rand() % (j + 1);
    swapTuple(&arr[index], &arr[j]);
    j--;
  }
}

TupleArr *manualTupleArr(void) {
  int n[] = {598, 110, 472, 278, 131, 313, 102, 934, 527, 677};
  char c[] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};

  TupleArr *tupleArr = malloc(sizeof(*tupleArr));
  tupleArr->arr = malloc(strlen(c) * sizeof(*(tupleArr->arr)));
  tupleArr->size = strlen(c);

  for (int i = 0; i < strlen(c); i++) {
    tupleArr->arr[i].n = n[i];
    tupleArr->arr[i].c = c[i];
  }
  return tupleArr;
}

int findMinIndex(Tuple *tuple_arr, int start, int end) {
  int min = tuple_arr[start].n;
  int index = start;
  for (int i = start; i < end; i++) {
    if (tuple_arr[i].n < min) {
      min = tuple_arr[i].n;
      index = i;
    }
  }
  return index;
}

int findMaxValue(Tuple *tuple_arr, int start, int end) {
  return tuple_arr[findMaxIndex(tuple_arr, start, end)].n;
}

int findMaxIndex(Tuple *tuple_arr, int start, int end) {
  int max = tuple_arr[start].n;
  int index = start;
  for (int i = start; i < end; i++) {
    if (tuple_arr[i].n > max) {
      max = tuple_arr[i].n;
      index = i;
    }
  }
  return index;
}

int findMinValue(Tuple *tuple_arr, int start, int end) {
  return tuple_arr[findMinIndex(tuple_arr, start, end)].n;
}

// Returns the first minimum value and the last maximum value
void findMinMaxIndex_FirstMinLastMax(Tuple *tuple_arr, int start, int end, int *minIndex, int *maxIndex) {
  int min = tuple_arr[start].n;
  int max = tuple_arr[start].n;
  *minIndex = start;
  *maxIndex = start;
  for (int i = start; i < end + 1; i++) {
    if (tuple_arr[i].n < min) {
      min = tuple_arr[i].n;
      *minIndex = i;
    }

    if (tuple_arr[i].n >= max) {
      max = tuple_arr[i].n;
      *maxIndex = i;
    }
  }
  return;
}

// Returns the first min and max value
void findMinMaxIndex_FirstMinFirstMax(Tuple *tuple_arr, int start, int end, int *minIndex, int *maxIndex) {
  int min = tuple_arr[start].n;
  int max = tuple_arr[start].n;
  *minIndex = start;
  *maxIndex = start;
  for (int i = start; i < end + 1; i++) {
    if (tuple_arr[i].n < min) {
      min = tuple_arr[i].n;
      *minIndex = i;
    }

    if (tuple_arr[i].n > max) {
      max = tuple_arr[i].n;
      *maxIndex = i;
    }
  }
  return;
}

void moveAcrossRight(Tuple *tuple_arr, int left, int right) {
  for (int i = right; i > left; i--) {
    tuple_arr[i] = tuple_arr[i - 1];
  }
}

void moveAcrossLeft(Tuple *tuple_arr, int left, int right) {
  for (int i = left; i < right; i++) {
    tuple_arr[i] = tuple_arr[i + 1];
  }
}

void printTupleArr(Tuple *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("(%d, %c)", arr[i].n, arr[i].c);
    if (i != size - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void freeTupleArr(TupleArr* tupleArr) {
  free(tupleArr->arr);
  free(tupleArr);
}
