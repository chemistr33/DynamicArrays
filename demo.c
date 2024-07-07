#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

// double-typed element print function
void
print_double (void *element)
{
  printf ("%f\n", *(double *)element);
}

// print integer callback
void
print_int (void *element)
{
  printf ("%d", *(int *)element);
}

// integer comparison callback
int
compare_int (const void *_a, const void *_b)
{
  int a = *(int *)_a;
  int b = *(int *)_b;

  if (a < b)
    {
      return -1;
    }
  else if (a == b)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

int
main (int argc, char **argv)
{
  Vector vec;

  init_vector (&vec, sizeof (double));
  register_user_print_fn (&vec, &print_int);
  register_user_sort_comparison_fn (&vec, &compare_int);
  push_back (&vec, &(int){ 6 });
  push_back (&vec, &(int){ 7 });
  push_back (&vec, &(int){ 1 });
  push_back (&vec, &(int){ 0 });
  push_back (&vec, &(int){ 0 });
  push_back (&vec, &(int){ 2 });
  push_back (&vec, &(int){ 4 });

  printVector (&vec, "original vector");

  sortVector (&vec, 0, vec.size);

  printVector (&vec, "sorted vector  ");

  Vector vec2;
  init_vector (&vec2, sizeof (double));
  register_user_print_fn (&vec2, &print_int);
  register_user_sort_comparison_fn (&vec2, &compare_int);
  push_back (&vec2, &(int){ -5 });
  push_back (&vec2, &(int){ 3 });
  push_back (&vec2, &(int){ 3 });
  push_back (&vec2, &(int){ 0 });
  push_back (&vec2, &(int){ 2 });
  push_back (&vec2, &(int){ 11 });
  push_back (&vec2, &(int){ 8 });
  push_back (&vec2, &(int){ 999 });

  printVector(&vec2, "       vec2");
  sortVector(&vec2,0,vec2.size);
  printVector(&vec2, "sorted vec2");


  free_vector(&vec);
  free_vector(&vec2);
  return 0;
}