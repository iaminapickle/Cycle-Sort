#ifndef TUPLEARRWRAPPER_H
#define TUPLEARRWRAPPER_H

#include "Tuple.h"

typedef struct tuple_arr_struct {
  Tuple *arr;
  int size;
} TupleArr;

TupleArr *initTupleArr(int size);
TupleArr *genRandomTupleArr(int size, int max, int seed);
void randomiseTuples(TupleArr *tupleArr, int max, int seed);
void randomiseTuples_Cons(TupleArr *tupleArr, int seed);
void randomiseTuples_Unique(TupleArr *tupleArr, int max, int n_unique, int seed);
void randomiseTuples_Max(TupleArr *tupleArr, int max, int seed);
void shuffleTupleArr(TupleArr *tupleArr);
TupleArr *manualTupleArr(void);

int findMinIndex(Tuple *tuple_arr, int start, int end);
int findMinValue(Tuple *tuple_arr, int start, int end);
int findMaxIndex(Tuple *tuple_arr, int start, int end);
int findMaxValue(Tuple *tuple_arr, int start, int end);
void findMinMaxIndex_FirstMinLastMax(Tuple *arr, int start, int end, int *minIndex, int *maxIndex);
void findMinMaxIndex_FirstMinFirstMax(Tuple *tuple_arr, int start, int end, int *minIndex, int *maxIndex);

void moveAcrossRight(Tuple *tuple_arr, int start, int end);
void moveAcrossLeft(Tuple *tuple_arr, int start, int end);

void printTupleArr(Tuple *arr, int size);
void freeTupleArr(TupleArr* tupleArr);
#endif
