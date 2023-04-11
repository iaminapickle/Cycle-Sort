#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../src/helper/TupleArr.h"
#include "AlgorithmArr.h"
#include "Algorithm.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

#define SIMPLE_TESTS false
#define NO_ALGORITHMS 3

unsigned int* generateSeeds(void);
void printBuffer(int nameLength, int longestNameLength);
void testAllAlgorithmCorrectness(AlgorithmArr *algos);
void testAllAlgorithmTime(AlgorithmArr *algos);
void runTimeTests(AlgorithmArr *algos, Results **results, int *noResults, unsigned int *seeds, int testSize, int maxVal);
void printTimeResults(AlgorithmArr *algos, Results **res, int noResults);
void addResults(Results **results, int i, double* res, int noAlgos, int testSize, int maxVal);
void freeResults(Results **results, int noResults);

void testAllAlgorithmCorrectness(AlgorithmArr *algos) {
  unsigned int *seeds = generateSeeds();

  printf("Testing for correctness:\n");
  for (int i = 0; i < algos->noAlgos; i++) {
    Algorithm cur = algos->arr[i];

    bool res = testAlgorithmCorrectness(cur, seeds);
    printf("%s:", cur.name);
    printBuffer(strlen(cur.name), algos->longestNameLength);

    if (res) {
      printf(GREEN "PASSED\n" RESET);
    } else {
      printf(RED "FAILED\n" RESET);
    }
  }
  printf("\n");

  free(seeds);
}

void testAllAlgorithmTime(AlgorithmArr *algos) {
  unsigned int *seeds = generateSeeds();
  int noResults = 0;

  if (SIMPLE_TESTS) {
    Results **results = malloc((NO_ALGORITHMS + 1) * sizeof(*results));
    runTimeTests(algos, results, &noResults, seeds, DEFAULT_TEST_SIZE, DEFAULT_MAX_VAL);
    printTimeResults(algos, results, noResults);
    freeResults(results, noResults);
  } else {
    for (int testSize = 10; testSize < 100000; testSize *= 10) {
      Results **results = malloc((NO_ALGORITHMS + 1) * sizeof(*results));
      for (int maxVal = 10; maxVal < 10000000; maxVal *= 10) {
        printf("Running tests for size = %d and maximum value %d\n", testSize, maxVal);
        runTimeTests(algos, results, &noResults, seeds, testSize, maxVal);
      }
      printTimeResults(algos, results, noResults);
      freeResults(results, noResults);
      noResults = 0;
    }
  }
  free(seeds);
}
unsigned int* generateSeeds(void) {
  unsigned int *seeds = malloc(DEFAULT_N_TESTS * sizeof(*seeds));
  seeds[0] = time(NULL);

  for (int i = 0; i < DEFAULT_N_TESTS - 1; i++) {
    srand(seeds[i]);
    seeds[i + 1] = rand();
  }
  return seeds;
}

void printBuffer(int nameLength, int longestNameLength) {
  for (int i = 0; i < 5 + (longestNameLength - nameLength); i++) {
    printf(" ");
  }
}

void runTests(AlgorithmArr *algos) {
  testAllAlgorithmCorrectness(algos);
  testAllAlgorithmTime(algos);
}

void addResults(Results **results, int i, double* res, int noAlgos, int testSize, int maxVal) {
  results[i] = malloc(sizeof(*results[i]));
  results[i]->arr = malloc(noAlgos * sizeof(*results[i]->arr));
  results[i]->min = res[0];
  results[i]->max = res[0];
  results[i]->longestResultLength = 0;

  for (int j = 0; j < noAlgos; j++) {
    int len = snprintf(NULL, 0, "%0.1f", res[j]);
    if (len > results[i]->longestResultLength) {
      results[i]->longestResultLength = len;
    }

    results[i]->arr[j] = res[j];

    if (res[j] > results[i]->max) {
      results[i]->max = res[j];
    }

    if (res[j] < results[i]->min) {
      results[i]->min = res[j];
    }
  }
  results[i]->testSize = testSize;
  results[i]->maxVal = maxVal;

  return;
}

AlgorithmArr *createEmptyAlgorithmArr(void) {
  AlgorithmArr* algos = malloc(sizeof(*algos));
  algos->longestNameLength = 0;
  algos->noAlgos = 0;

  return algos;
}

void addAlgorithm(AlgorithmArr *algos, void (*sort)(TupleArr*), bool isStable, char* name) {
  int i = algos->noAlgos;
  algos->arr = realloc(algos->arr, (i + 1) * sizeof(*(algos->arr)));

  algos->arr[i].name = malloc((strlen(name) + 1) * sizeof(*algos->arr[i].name));
  strcpy(algos->arr[i].name, name);
  algos->arr[i].isStable = isStable;
  algos->arr[i].sort = sort;

  (algos->noAlgos)++;

  if (strlen(name) > algos->longestNameLength) {
    algos->longestNameLength = strlen(name);
  }
}

void printTimeResults(AlgorithmArr *algos, Results **results, int noResults) {
  printf("Testing for time taken:\n");
  for (int i = 0; i < algos->noAlgos; i++) {
    Algorithm cur = algos->arr[i];
    printf("%s:", cur.name);
    printBuffer(strlen(cur.name), algos->longestNameLength);

    for (int j = 0; j < noResults; j++) {
      if (results[j]->arr[i] == results[j]->min) {
        printf(GREEN);
      } else if (results[j]->arr[i] == results[j]->max) {
        printf(RED);
      }
      int len = snprintf(NULL, 0, "%0.1f", results[j]->arr[i]);
      printf("  %0.1lf  " RESET, results[j]->arr[i]);
      for (int k = 0; k < results[j]->longestResultLength - len; k++) {
        printf(" ");
      }

    }
    printf("\n");
  }
  printf("\n");
}

void runTimeTests(AlgorithmArr *algos, Results **results, int *noResults, unsigned int *seeds, int testSize, int maxVal) {
  double res[algos->noAlgos];
  for (int i = 0; i < algos->noAlgos; i++) {
    printf("Running %s...\n", algos->arr[i].name);
    res[i] = testAlgorithmTime(algos->arr[i], seeds, testSize, maxVal);
  }

  (*noResults)++;
  addResults(results, *noResults - 1, res, algos->noAlgos, testSize, maxVal);
  return;
}

void freeResults(Results **results, int noResults) {
  for (int i = 0; i < noResults; i++) {
    free(results[i]->arr);
    free(results[i]);
  }
  free(results);
}

void freeAlgorithmArr(AlgorithmArr *algos) {
  for (int i = 0; i < algos->noAlgos; i++) {
    free(algos->arr[i].name);
  }
  free(algos->arr);
  free(algos);
}
