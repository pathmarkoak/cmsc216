#include <stdio.h>
#include<assert.h>
#include "functions.h"

/* Student tests for compare_rectantangles */

int main(void) {
  assert(compare_rectangles(4, 3, 6, 2) == 0);
  assert(compare_rectangles(4, 1, 2, 2) == 0);
  assert(compare_rectangles(1, 5, 100, 1) == -1);
  assert(compare_rectangles(1, 100, 1, 5) == 1); 
  assert(compare_rectangles(-1, 0, 0, 0) == -2);
  assert(compare_rectangles(0, 0, 0, 0) == 0);
  assert(compare_rectangles(0, 1, 1, 1) == -1);
  assert(compare_rectangles(1, 1, 0, 0) == 1);
  assert(compare_rectangles(-1, -1, -1, -1) == -2); 
  assert(compare_rectangles(-1, -1, 0, 0) == -2); 
  assert(compare_rectangles(2, 20, 20, 2) == 0); 
  assert(compare_rectangles(2, 5, 100, 100) == -1);

  printf("\n This test has passed!\n");
  
  return 0;
}
