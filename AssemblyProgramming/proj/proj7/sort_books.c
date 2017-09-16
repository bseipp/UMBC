extern int bookcmp(const struct book *, const struct book *);
typedef int (* COMP_FUNC_PTR) (const struct book *, const struct book *);

void sort_books(struct book books[], int numBooks) {
  qsort(books, numBooks, sizeOf(book), (COMP_FUNC_PTR) &bookcmp);
}
