#include <stdio.h>
#include <assert.h>
#include "functions.h"

/* CMSC 216, Spring 2023, Project #1
 * Public test 3 (public3.c)
 *
 * Tests calling pell(0).
 *
 * (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  assert(pell(0) == 0);

  printf("\nThis test has passed!\n");

  return 0;
}
