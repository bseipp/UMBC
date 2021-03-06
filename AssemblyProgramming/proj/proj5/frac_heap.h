/* frac_heap.h */

typedef struct {
  signed char sign;
  unsigned int denominator;
  unsigned int numerator;
} fraction;

void init_heap();
void dump_heap();
void del_frac(fraction *fp);
fraction* new_frac();
