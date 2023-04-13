#include "../src/helper/TupleArr.h"
#include "../src/wiki/wiki_cycle_sort.h"
#include "../src/general/general_cycle_sort.h"
#include "../src/special/special_cycle_sort.h"
#include "AlgorithmArr.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  AlgorithmArr *algos = createEmptyAlgorithmArr();
  //addAlgorithm(algos, &wikiCycleSort, false, "Wiki Cycle Sort");
  addAlgorithm(algos, &generalCycleSort, false, "General Cycle Sort");
  //addAlgorithm(algos, &specialCycleSort, false, "Special Cycle Sort");

  runTests(algos);
  freeAlgorithmArr(algos);
  return 0;
}
