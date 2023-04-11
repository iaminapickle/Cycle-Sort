#include "Algorithm.h"

#ifndef ALGORITHM_ARR_H
#define ALGORITHM_ARR_H

typedef struct algorithm_arr_struct {
  Algorithm *arr;
  int noAlgos;
  int longestNameLength;
} AlgorithmArr;

typedef struct results_struct {
  double *arr;
  double min;
  double max;
  int longestResultLength;
  int testSize;
  int maxVal;
} Results;

AlgorithmArr *createEmptyAlgorithmArr(void);
void runTests(AlgorithmArr *algos);
void addAlgorithm(AlgorithmArr *algos, void (*sort)(TupleArr*), bool isStable, char* name);
void freeAlgorithmArr(AlgorithmArr *algos);
#endif
