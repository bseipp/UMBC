/*
 *  File: main6.c
 *
 *  This file tests out the functions in frac_heap.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

fraction *init_frac (signed char s, unsigned int n, unsigned int d) {
   
  fraction *fp ;

  fp = new_frac() ;
  fp->sign = s ;
  fp->numerator = n ;
  fp->denominator = d ;

  return fp ;
}

int main() {
  init_heap() ;
  fraction* fp = new_frac();
  dump_heap();
  fraction* fp1 = new_frac();
  dump_heap();
  fraction* fp2 = new_frac();
  dump_heap();
  fraction* fp3 = new_frac();
  dump_heap();
  fraction* fp4 = new_frac();
  dump_heap();
  fraction* fp5 = new_frac();
  dump_heap();
  fraction* fp6 = new_frac();
  dump_heap();
  fraction* fp7 = new_frac();
  dump_heap();
  fraction* fp8 = new_frac();
  dump_heap();
  fraction* fp9 = new_frac();
  dump_heap();

  fp->sign = 1;
  fp1->sign = 1;
  fp2->sign = 1;
  fp3->sign = 1;
  fp4->sign = 1;
  fp5->sign = 1;
  fp6->sign = 1;
  fp7->sign = 1;
  fp8->sign = 1;
  fp9->sign = 1;
  
  printf("\nDeleting fraction pointer, pointer is valued at: %p\n", fp1);
  del_frac(fp1);
  dump_heap();

  printf("\nDeleting fraction pointer, pointer is valued at: %p\n", fp2);
  del_frac(fp2);
  dump_heap();

  printf("\nDeleting fraction pointer, pointer is valued at: %p\n", fp3);
  del_frac(fp3);
  dump_heap();

  return 0 ;
}
