/*
 *  File: main5.c
 *
 *  This file tests out the functions in frac_heap.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

int main() {
   fraction  *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9, *fp10, *fp11, *fp12, *fp13, *fp14, *fp15, *fp16, *fp17, *fp18, *fp19, *fp20, *fp21; 

   init_heap() ;
   
   fp1 = new_frac() ;
   fp1->sign = 0 ;
   fp1->numerator = 1 ;
   fp1->denominator = 2 ;

   fp2 = new_frac() ;
   fp2->sign = 0 ;
   fp2->numerator = 1 ;
   fp2->denominator = 2 ;

   fp3 = new_frac() ;
   fp3->sign = 0 ;
   fp3->numerator = 1 ;
   fp3->denominator = 2 ;

   fp4 = new_frac() ;
   fp4->sign = 0 ;
   fp4->numerator = 1 ;
   fp4->denominator = 2 ;

   fp5 = new_frac() ;
   fp5->sign = 0 ;
   fp5->numerator = 1 ;
   fp5->denominator = 2 ;

   fp6 = new_frac() ;
   fp6->sign = 0 ;
   fp6->numerator = 1 ;
   fp6->denominator = 2 ;

   fp7 = new_frac() ;
   fp7->sign = 0 ;
   fp7->numerator = 1 ;
   fp7->denominator = 2 ;

   fp8 = new_frac() ;
   fp8->sign = 0 ;
   fp8->numerator = 1 ;
   fp8->denominator = 2 ;

   fp9 = new_frac() ;
   fp9->sign = 0 ;
   fp9->numerator = 1 ;
   fp9->denominator = 2 ;

   fp10 = new_frac() ;
   fp10->sign = 0 ;
   fp10->numerator = 1 ;
   fp10->denominator = 2 ;

   fp11 = new_frac() ;
   fp11->sign = 0 ;
   fp11->numerator = 1 ;
   fp11->denominator = 2 ;

   fp12 = new_frac() ;
   fp12->sign = 0 ;
   fp12->numerator = 1 ;
   fp12->denominator = 2 ;

   fp13 = new_frac() ;
   fp13->sign = 0 ;
   fp13->numerator = 1 ;
   fp13->denominator = 2 ;

   fp14 = new_frac() ;
   fp14->sign = 0 ;
   fp14->numerator = 1 ;
   fp14->denominator = 2 ;

   fp15 = new_frac() ;
   fp15->sign = 0 ;
   fp15->numerator = 1 ;
   fp15->denominator = 2 ;

   fp16 = new_frac() ;
   fp16->sign = 0 ;
   fp16->numerator = 1 ;
   fp16->denominator = 2 ;

   fp17 = new_frac() ;
   fp17->sign = 0 ;
   fp17->numerator = 1 ;
   fp17->denominator = 2 ;

   dump_heap() ; 

   fp18 = new_frac() ;
   fp18->sign = 0 ;
   fp18->numerator = 1 ;
   fp18->denominator = 2 ;

   dump_heap() ; 
   del_frac(fp1);

   fp19 = new_frac() ;
   fp19->sign = 0 ;
   fp19->numerator = 1 ;
   fp19->denominator = 2 ;

   dump_heap() ; 

   fp20 = new_frac() ;
   fp20->sign = 0 ;
   fp20->numerator = 1 ;
   fp20->denominator = 2 ;

   dump_heap() ; 

   fp21 = new_frac() ;
   
   printf ("Fraction 21 is: %p\n\n", fp21);

   return 0 ;
}
