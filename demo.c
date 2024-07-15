#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

// DEBUGGING

#define PRINT_CTRL_WORD(vec)                                                  \
  do                                                                          \
    {                                                                         \
      printf (ANSI_GREEN "## CTRL_WORD:%ld ##\n" ANSI_RESET, (vec)->ctrl_word);                     \
    }                                                                         \
  while (0)

// Print callback function for type double elements
void
print_double (void *element)
{
  printf ("%f\n", *(double *)element);
}

// Print callback function for type int elements
void
print_int (void *element)
{
  printf (ANSI_RED "%d" ANSI_RESET, *(int *)element);
}

// Comparison callback function for two int elements
// -1  a < b
//  0  a == b
//  1  a > b
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
  // Vector vec;

  // init_vector (&vec, sizeof (double));
  // register_user_print_fn (&vec, &print_int);
  // register_user_compare_fn (&vec, &compare_int);
  // push_back (&vec, &(int){ 6 });
  // push_back (&vec, &(int){ 7 });
  // push_back (&vec, &(int){ 1 });
  // push_back (&vec, &(int){ 0 });
  // push_back (&vec, &(int){ 0 });
  // push_back (&vec, &(int){ 2 });
  // push_back (&vec, &(int){ 4 });

  // printVector (&vec, "original vector");

  // sortVector (&vec, 0, vec.size);

  // printVector (&vec, "sorted vector  ");

  // Vector vec2;
  // init_vector (&vec2, sizeof (int));
  // register_user_print_fn (&vec2, &print_int);
  // register_user_compare_fn (&vec2, &compare_int);

  // push_back (&vec2, &(int){ -5 });
  // push_back (&vec2, &(int){ 3 });
  // push_back (&vec2, &(int){ 3 });
  // push_back (&vec2, &(int){ 0 });
  // push_back (&vec2, &(int){ 2 });
  // push_back (&vec2, &(int){ 11 });
  // push_back (&vec2, &(int){ 8 });
  // push_back (&vec2, &(int){ 999 });

  // printVector (&vec2, "       vec2");
  // sortVector (&vec2, 0, vec2.size);
  // printVector (&vec2, "sorted vec2");

  // free_vector (&vec);
  // free_vector (&vec2);

  Vector vec3;
  PRINT_CTRL_WORD (&vec3);
  init_vector (&vec3, sizeof (int));
  PRINT_CTRL_WORD (&vec3);
  register_user_print_fn (&vec3, &print_int);
  register_user_compare_fn (&vec3, &compare_int);

  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 3 });
  push (&vec3, &(int){ 9 });
  push (&vec3, &(int){ 9 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 0 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 3 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 555 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 7 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 88000 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 22 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 11 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 45 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 1 });
  push (&vec3, &(int){ 10 });

  puts ("");
  printVector (&vec3, "Unsorted vec3");

  // search test

  int number = 555;
  void *muh_number = &number;
  PRINT_CTRL_WORD (&vec3);
  sortVector (&vec3, 0, vec3.size);
  printVector (&vec3, "  Sorted vec3");
  PRINT_CTRL_WORD (&vec3);
  printf ("Looking for *FIRST* 555...\n");
  printf ("Result: %d\n", searchVector (&vec3, muh_number, FIRST));
  printf ("Element at vec.data[%d] = %d\n",
          searchVector (&vec3, muh_number, FIRST),
          *(int *)at (&vec3, searchVector (&vec3, muh_number, FIRST)));

  printf ("Looking for *LAST* 555...\n");
  printf ("Result: %d\n", searchVector (&vec3, muh_number, LAST));
  printf ("Element at vec.data[%d] = %d\n",
          searchVector (&vec3, muh_number, LAST),
          *(int *)at (&vec3, searchVector (&vec3, muh_number, LAST)));

  return 0;
}