#include <stdio.h>
#include <assert.h>
#include "functions.h"

/* Student tests for function 3 */

int main(void) {
  assert(pell(0) == 0); 
  assert(pell(1) == 1); 
  assert(pell(2) == 2);
  assert(pell(3) == 5); 
  assert(pell(5) == 29);
  assert(pell(6) == 70); 
  assert(pell(7) == 169);
  assert(pell(8) == 408);
  assert(pell(9) == 985); 
  assert(pell(10) == 2378); 
  assert(pell(45) == 59341817924539925);
  assert(pell(-1) == -1); 
  assert(pell(-50) == -1); 
  
  printf("\nThis test has passed!\n");

  return 0;
}
