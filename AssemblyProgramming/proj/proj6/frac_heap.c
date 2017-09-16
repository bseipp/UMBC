#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

union fractionBlock {
  fraction f;
  union fractionBlock* next;
};

union fractionBlock* firstBlock;
union fractionBlock fb;

void init_heap() {
  firstBlock = NULL;
}

fraction* new_frac() {
  if (firstBlock == NULL){
    firstBlock = (union fractionBlock*) malloc(sizeof(fb));
    if (firstBlock == NULL){
      printf("Warning, out of memory! Please buy a better computer.");
      exit(0);
    }

    union fractionBlock* fb2 = (union fractionBlock*) malloc(sizeof(fb));
    if (fb2 == NULL){
      printf("Warning, out of memory! Please buy a better computer.");
      exit(0);
    }

    union fractionBlock* fb3 = (union fractionBlock*) malloc(sizeof(fb));
    if (fb3 == NULL){
      printf("Warning, out of memory! Please buy a better computer.");
      exit(0);
    }

    union fractionBlock* fb4 = (union fractionBlock*) malloc(sizeof(fb));
    if (fb4 == NULL){
      printf("Warning, out of memory! Please buy a better computer.");
      exit(0);
    }

    union fractionBlock* fb5 = (union fractionBlock*) malloc(sizeof(fb));    
    if (fb5 == NULL){
      printf("Warning, out of memory! Please buy a better computer.");
      exit(0);
    }    

    firstBlock->next = fb2;
    fb2->next = fb3;
    fb3->next = fb4;
    fb4->next = NULL;
    printf("Called malloc(%d): returned %p\n", (int)(sizeof(fb)*5), fb5); 
    return (&fb5->f);

  } else {
    union fractionBlock* temp = firstBlock;
    if (firstBlock->next == NULL){
      firstBlock = NULL;
    } else {
      firstBlock = firstBlock->next;
    }
    return (&temp->f);
  }
}

void del_frac(fraction *fp){
  union fractionBlock* temp = firstBlock;    
  firstBlock = (union fractionBlock*) fp;
  firstBlock->next = temp;
}

void dump_heap() {

  printf("\n**** BEGIN HEAP DUMP ****\n\n");

  if (firstBlock == NULL){
    printf("Free list is empty\n");
  } else {
    union fractionBlock* temp = firstBlock;
    while (temp != NULL) {
      printf("%p\n", temp);
      temp = temp->next;
    }
  }
  printf("\n**** END HEAP DUMP ****\n");
}
