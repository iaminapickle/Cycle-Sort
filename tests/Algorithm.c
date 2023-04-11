#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "../src/helper/TupleArr.h"
#include "Algorithm.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

#define OUTPUT true

bool checkArrStable(TupleArr* tupleArr);
bool checkArrUnstable(TupleArr* tupleArr);
long long timeInMilliseconds(void);

bool testAlgorithmCorrectness(Algorithm algorithm, unsigned int* seeds) {
  TupleArr* tupleArr = initTupleArr(DEFAULT_TEST_SIZE);
  TupleArr* copy = initTupleArr(DEFAULT_TEST_SIZE);
  bool flag = true;

  for (int i = 0; i < DEFAULT_N_TESTS; i++) {


    if (i < DEFAULT_N_TESTS) {
      randomiseTuples_Max(tupleArr, DEFAULT_MAX_VAL, seeds[i]);
    } else {
      randomiseTuples_Max(tupleArr, 2, seeds[i]);
    }

    if (strcmp(algorithm.name, "Special Cycle Sort") == 0) {
      randomiseTuples_Cons(tupleArr, seeds[i]);
    }

    for (int j = 0; j < DEFAULT_TEST_SIZE; j++) {
      copy->arr[j] = tupleArr->arr[j];
    }

    (*algorithm.sort)(tupleArr);
    bool res = (algorithm.isStable) ? checkArrStable(tupleArr) : checkArrUnstable(tupleArr);

    if (res == false) {
      flag = false;
    }

    if (OUTPUT == false) {
      continue;
    }

    if (res == false) {
      printf("Test: ");
      printf(RED "failed\n" RESET);
      printf("Input:\n");
      printTupleArr(copy->arr, DEFAULT_TEST_SIZE);
      printf("Output:\n");
      printTupleArr(tupleArr->arr, DEFAULT_TEST_SIZE);
    };
  }
  freeTupleArr(tupleArr);
  freeTupleArr(copy);
  return flag;
}

double testAlgorithmTime(Algorithm algorithm, unsigned int* seeds, int testSize, int maxVal) {
  TupleArr* tupleArr = initTupleArr(testSize);
  long long time_ms = 0;

  for (int i = 0; i < DEFAULT_N_TESTS; i++) {
    randomiseTuples_Max(tupleArr, maxVal, seeds[i]);

    if (strcmp(algorithm.name, "Special Cycle Sort") == 0) {
      randomiseTuples_Cons(tupleArr, seeds[i]);
    }

    long long start = timeInMilliseconds();
    (*algorithm.sort)(tupleArr);
    long long end = timeInMilliseconds();
    time_ms += end - start;
  }
  free(tupleArr->arr);
  free(tupleArr);
  return (double)time_ms / (DEFAULT_N_TESTS);
}

bool checkArrStable(TupleArr* tupleArr) {
  Tuple *arr = tupleArr->arr;
  int max = findMaxValue(tupleArr->arr, 0, tupleArr->size);

  int *count = calloc(max + 1, sizeof(*count));
  for (int i = 0; i < tupleArr->size - 1; i++) {
    if (arr[i].n > arr[i + 1].n) {
      printf("size = %d. at index %d i = %d || i + 1 = %d\n",tupleArr->size, i, arr[i].n, arr[i + 1].n);
      return false;
    }

    if (arr[i].c - 97 != count[arr[i].n]) {
      printf("B");
      return false;
    }
    count[arr[i].n] += 1;
  }
  free(count);
  return true;
}

bool checkArrUnstable(TupleArr* tupleArr) {
  Tuple *arr = tupleArr->arr;

  for (int i = 0; i < DEFAULT_TEST_SIZE - 1; i++) {
    if (arr[i].n > arr[i + 1].n) {
      return false;
    }
  }

  return true;
}

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}
