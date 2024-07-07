#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

// double-typed element print function
void
print_double (void *element)
{
  printf ("%f\n", *(double *)element);
}

int
main (int argc, char **argv)
{
  Vector vec;

  init_vector (&vec, sizeof (double));
  register_user_print_fn (&vec, &print_double);

  push (&vec, &(double){ 1.1 });
  push (&vec, &(double){ 2.2 });
  push (&vec, &(double){ 3.3 });
  push (&vec, &(double){ 4.4 });
  push (&vec, &(double){ 5.55555 });
  push (&vec, &(double){ 6.6 });
  push (&vec, &(double){ 7.7 });
  push (&vec, &(double){ 8.8 });
  push (&vec, &(double){ 9.9 });

  printf ("Size: %zu, Capacity: %zu\n", vec.size, vec.capacity);
  printVector (&vec, print_double);

  printf ("\n---------------------------------------------------------\n");

  double temp = *(double *)(vec.data + 4 * vec.element_size);
  insert (&vec, 0, &temp);
  push_back (&vec, &temp);
  printf ("Size: %zu, Capacity: %zu\n", vec.size, vec.capacity);

  shrink_to_fit (&vec);
  puts ("after shrink_to_fit()...");
  printf ("Size: %zu, Capacity: %zu\n", vec.size, vec.capacity);
  printVector (&vec, print_double);

  void *someElement = at (&vec, 7);
  printf ("%f is the element at index 7\n", *(double *)someElement);
  printf ("\n---------------------------------------------------------\n");

  insert (&vec, 10, &(double){ 9.999999 });
  alterElement (&vec, 11, &(double){ 12345.6789 });

  printVector (&vec, print_double);

  printf ("\nOk let's check some more stuff, note we changed [11]...\n");
  printf ("front() = %f\nat(&vec,10) = %f\nback() = %f\n",
          *(double *)(front (&vec)), *(double *)at (&vec, 10),
          *(double *)back (&vec));

  printf ("\n\nClear() test...\n");
  clear (&vec);
  printVector (&vec, print_double);
  free_vector (&vec);
  printVector (&vec, print_double);
  return 0;
}

#if 0

void printVector(Vector *vec)
{
	for (int i = 0; i < vec->size - 1; i++)
	{
		printf("[%d] = %zu\n",
			   i,
			   *(double *)((char *)vec->data + i * vec->element_size));
	}
}

#endif