#include "functions.h"


short compare_rectangles(int l1, int w1, int l2, int w2) {
  long  area1 = l1*w1;
  long area2 = l2*w2; 

  if (l1 <  0 || w1 <  0 || l2 < 0 || w2 <  0) { 
    return -2; 
  } else if (area1 > area2) {
    return 1;
  } else if (area1 < area2) {
    return -1;
  } else {
    return 0;
  }
}

int ith_factor(int a, int b, int i) {
  int count = 0;
  int tracker = 1;
  int smaller_num;
  int result;  
 
  if (a < 0) {
    a = -1 * a;  
  }

  if (b < 0) {
    b = -1 * b;
  }

  if (i <=  0) {
    return -1; 
  }

  if (a > b) {
    smaller_num = b;  
  } else { 
    smaller_num = a; 
  }

  while (count < i && tracker <= smaller_num) {
    if ((a % tracker  == 0) && (b % tracker == 0)) {
      result = tracker; 
      count++;
    }
    tracker++;
  }

  if (count == i) {
   return result; 
  } else {
     return -1; 
  }
}

long pell(short n) {
  long tracker1 = 0;
  long tracker2 = 1;
  short i;
  long result = 0;

  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1; 
  } else if (n < 0) { 
    return -1; 
} else {
    for (i = 2; i <= n; i++) {
      result = (2 * tracker2) + tracker1;
      tracker1 = tracker2;
      tracker2 = result; 
    }
  }
  return result; 
}
