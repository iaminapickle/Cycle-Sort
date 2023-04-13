#include <stdbool.h>
#include "../src/helper/TupleArr.h"

#ifndef ALGORITHM_H
#define ALGORITHM_H

#define DEFAULT_TEST_SIZE 10
#define DEFAULT_MAX_VAL 10
#define DEFAULT_N_TESTS 20

typedef struct algorithm_struct {
  void (*sort)(TupleArr*);
  char* name;
  bool isStable;
} Algorithm;

bool testAlgorithmCorrectness(Algorithm algorithm, unsigned int* seeds);
double testAlgorithmTime(Algorithm algorithm, unsigned int* seeds, int testSize, int maxVal);

#endif
