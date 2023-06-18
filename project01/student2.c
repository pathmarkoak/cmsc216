#include <stdio.h>
#include<assert.h>
#include "functions.h"

/* Student tests for compare_rectangles */

int main(void) {
  assert(ith_factor(6240, 288, 1) == 1); 
  assert(ith_factor(6240, 288, 2) == 2);
  assert(ith_factor(6240, 288, 3) == 3);
  assert(ith_factor(6240, 288, 4) == 4);
  assert(ith_factor(6240, 288, 5) == 6);
  assert(ith_factor(6240, 288, 12) == 96); 
  assert(ith_factor(6240, 288, 15) == -1);
  assert(ith_factor(624, 48, 7) == 12); 
  assert(ith_factor(-624, 48, 7) == 12);
  assert(ith_factor(624, -48, 7) == 12);
  assert(ith_factor(-624, -48, 7) == 12);
  assert(ith_factor(624, 48, 0) == -1);
  assert(ith_factor(0, 0, 5) == -1);
  assert(ith_factor(-1, -1, 100) == -1);
  assert(ith_factor(-1, -1, 1) == 1);
  assert(ith_factor(1, -1, 1) == 1);
  assert(ith_factor(0, 0, 0) == -1); 
  assert(ith_factor(0, 0, 1) == -1);
  assert(ith_factor(-4, -4, 3) == 4); 
  assert(ith_factor(-8, 16, 4) == 8); 
  assert(ith_factor(6240, 288, -5) == -1); 
  

  printf("\n This test has passed!\n");

  return 0;
}
