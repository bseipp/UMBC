/*
 *  File: main6.c
 *
 *  This file tests out the functions in frac_heap.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

#define ARRAY_SIZE 100

fraction *init_frac (signed char s, unsigned int n, unsigned int d) {
   
  fraction *fp ;

  fp = new_frac() ;
  fp->sign = s ;
  fp->numerator = n ;
  fp->denominator = d ;

  return fp ;
}

int main() {
  fraction * fracArray[ARRAY_SIZE] = {};
  init_heap() ;
  int x;
  for (x = 0; x < ARRAY_SIZE; x++) {
    fracArray[x] = new_frac();
    fracArray[x]->sign = -1 ;
    fracArray[x]->numerator = 2 ;
    fracArray[x]->denominator = 3 ;
    dump_heap();
  }

  return 0 ;
}
