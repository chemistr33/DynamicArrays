#include "vector.h"
/**
 *  Callback Registration
 *
 */

// Register LibUser Print Function
void
register_user_print_fn (Vector *vec, print_fptr user_print_fn)
{
  NULLCHECK (vec);
  vec->user_print_fn = user_print_fn;
}

// Register user sort comparison function
void
register_user_sort_comparison_fn (Vector *vec, compare_fptr user_sort_fn)
{
  NULLCHECK (vec);
  vec->user_sort_compare_fn = user_sort_fn;
}

// Register user search comparison function
void
register_user_search_comparison_fn (Vector *vec,
                                    search_fptr user_search_compare_fn)
{
  NULLCHECK (vec);
  vec->user_search_compare_fn = user_search_compare_fn;
}

/**
 * Callback Functions
 *
 */

// Generic print function, requires user to register their own callback
// function conforming to type `void (*foo)(void *)`
void
printVector (Vector *vec, print_fptr user_print_fn)
{
  // Check if Vector is NULL
  NULLCHECK (vec->data);

  // Check if print callback function was ever registers by user
  if (!vec->user_print_fn)
    {
      fprintf (stderr, "Print function not registered by user.\n");
      return;
    }

  // Check if Vector exists but is empty
  if (vec->size <= 0)
    {
      printf ("printVector: Vector Empty, returning.\n");
      return;
    }

  for (size_t i = 0; i < vec->size; i++)
    {
      printf ("[%zu] = ", i);
      vec->user_print_fn ((char *)vec->data + i * vec->element_size);
    }
}

// MergeSort & helper function employing generic comparison callback
void
merge (Vector *vec, size_t left, size_t mid, size_t right, compare_fptr comp,
       void *temp)
{
  size_t i = left, j = mid, k = 0;

  while (i < mid && j < right)
    {
      if (comp ((char *)vec->data + i * vec->element_size,
                (char *)vec->data + j * vec->element_size)
          <= 0)
        {
          memcpy ((char *)temp + k * vec->element_size,
                  (char *)vec->data + i * vec->element_size,
                  vec->element_size);
          i++;
        }
      else
        {
          memcpy ((char *)temp + k * vec->element_size,
                  (char *)vec->data + j * vec->element_size,
                  vec->element_size);
          j++;
        }
      k++;
    }

  while (i < mid)
    {
      memcpy ((char *)temp + k * vec->element_size,
              (char *)vec->data + i * vec->element_size, vec->element_size);
      i++;
      k++;
    }

  while (j < right)
    {
      memcpy ((char *)temp + k * vec->element_size,
              (char *)vec->data + j * vec->element_size, vec->element_size);
      j++;
      k++;
    }

  memcpy ((char *)vec->data + left * vec->element_size, temp,
          k * vec->element_size);
}

void
mergesort (Vector *vec, size_t left, size_t right, compare_fptr comp)
{
  // Base case: if length of segment is 1, it's already sorted.
  if (right - left <= 1)
    {
      return;
    }

  size_t mid = left + (right - left) / 2;
  mergesort (vec, left, mid, comp);
  mergesort (vec, mid, right, comp);

  // Allocate a temp Vector, here's your space complexity
  void *temp = malloc ((right - left) * vec->element_size);
  MEMCHECK (temp);

  // Merge all the individual
  merge (vec, left, mid, right, comp, temp);
  free (temp);
}

/**
 *  Initialize & Destroy
 */

// Initializes a vector
void
init_vector (Vector *vec, size_t elem_size)
{
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
  vec->element_size = elem_size;
}

// Destroy vector's allocated memory
void
free_vector (Vector *vec)
{
  free (vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}

/**
 * Capacity Management
 */

// Return number of elements in use
size_t
size (Vector *vec)
{
  return vec->size;
}

// Return number of elements vector could hold w/o resize operation
size_t
capacity (Vector *vec)
{
  return vec->capacity;
}

// Ensure vector capacity is >= specified capacity
void
reserve (Vector *vec, size_t new_cap)
{
  // If specified capacity > current capacity, allocate more space
  if (new_cap > vec->capacity)
    {
      void *new_data = realloc (vec->data, new_cap * vec->element_size);
      MEMCHECK (new_data);
      vec->data = new_data;
      vec->capacity = new_cap;
    }
}

// Resize vector to specified size, reallocate as necessary
void
resize (Vector *vec, size_t new_size)
{
  // If new_size > current capacity, increase capacity
  if (new_size > vec->capacity)
    {
      reserve (vec, new_size);
    }

  // If new_size > current size, (size increasing), initialize new elems to 0
  if (new_size > vec->size)
    {
      memset ((char *)vec->data + vec->size * vec->element_size, 0,
              (new_size - vec->size) * vec->element_size);
    }
  else if (new_size < vec->size)
    {
      // If decreasing size, zero out the unused elements
      memset ((char *)vec->data + new_size * vec->element_size, 0,
              (vec->size - new_size) * vec->element_size);
    }

  // Update size to new size
  vec->size = new_size;
}

// Reduce capacity to fit the current size
void
shrink_to_fit (Vector *vec)
{
  if (vec->capacity > vec->size)
    {
      void *new_data = realloc (vec->data, vec->size * vec->element_size);
      MEMCHECK (new_data);
      vec->data = new_data;
      vec->capacity = vec->size;
    }
}

// Access element at specific index
void *
at (Vector *vec, size_t index)
{
  if (index >= vec->size || index < 0)
    {
      fprintf (stderr, "Index out of bounds\n");
      exit (EXIT_FAILURE);
    }
  return (char *)vec->data + index * vec->element_size;
}

// Return first element (index 0)
void *
front (Vector *vec)
{
  if (vec->size == 0)
    {
      fprintf (stderr, "Vector is empty\n");
      exit (EXIT_FAILURE);
    }
  return vec->data;
}

// Return last element (index size - 1)
void *
back (Vector *vec)
{
  if (vec->size == 0)
    {
      fprintf (stderr, "Vector is empty\n");
      exit (EXIT_FAILURE);
    }
  return (char *)vec->data + (vec->size - 1) * vec->element_size;
}

// Return pointer to the data array
void *
data (Vector *vec)
{
  return vec->data;
}

// Add an element to the front of the vector
void
push (Vector *vec, void *value)
{
  if (vec->size == vec->capacity)
    {
      reserve (vec, vec->capacity == 0 ? 1 : vec->capacity * 2);
    }

  memmove ((char *)vec->data + vec->element_size, (char *)vec->data,
           vec->size * vec->element_size);

  memcpy ((char *)vec->data, value, vec->element_size);

  vec->size++;
}

// Pop element off the front of the vector
void
pop (Vector *vec)
{
  if (vec->size == 0)
    {
      fprintf (stderr, "Vector is empty\n");
      exit (EXIT_FAILURE);
    }

  memmove ((char *)vec->data, (char *)vec->data + vec->element_size,
           (vec->size - 1) * vec->element_size);

  memset ((char *)vec->data + vec->size * vec->element_size, 0,
          vec->element_size);

  vec->size--;
}

// Add an element to the end of the vector
void
push_back (Vector *vec, void *value)
{
  if (vec->size == vec->capacity)
    {
      reserve (vec, vec->capacity == 0 ? 1 : vec->capacity * 2);
    }
  memcpy ((char *)vec->data + vec->size * vec->element_size, value,
          vec->element_size);
  vec->size++;
}

// Remove the last element of the vector
void
pop_back (Vector *vec)
{
  if (vec->size == 0)
    {
      fprintf (stderr, "Vector is empty\n");
      exit (EXIT_FAILURE);
    }
  vec->size--;
}

// Insert an element at a specific index
void
insert (Vector *vec, size_t index, void *value)
{
  if (index >= vec->size)
    {
      fprintf (stderr, "Index out of bounds\n");
      exit (EXIT_FAILURE);
    }
  if (vec->size == vec->capacity)
    {
      reserve (vec, vec->capacity == 0 ? 1 : vec->capacity * 2);
    }
  memmove ((char *)vec->data + (index + 1) * vec->element_size,
           (char *)vec->data + index * vec->element_size,
           (vec->size - index) * vec->element_size);
  memcpy ((char *)vec->data + index * vec->element_size, value,
          vec->element_size);
  vec->size++;
}

// Alters element at specified index
void
alterElement (Vector *vec, size_t index, void *value)
{
  // check if vector empty
  if (vec->size < 1)
    {
      fprintf (stderr,
               "Vector empty, add an element to use alterElement().\n");
      exit (EXIT_FAILURE);
    }
  // check if element exists & validate index argument boundaries
  if (index >= vec->size)
    {
      fprintf (stderr, "Invalid element index\n");
      exit (EXIT_FAILURE);
    }

  // Copy over the specified index with specified value
  memcpy ((char *)vec->data + index * vec->element_size, value,
          vec->element_size);
}

// Erase an element at a specific index
void
erase (Vector *vec, size_t index)
{
  if (index >= vec->size)
    {
      fprintf (stderr, "Index out of bounds\n");
      exit (EXIT_FAILURE);
    }
  memmove ((char *)vec->data + index * vec->element_size,
           (char *)vec->data + (index + 1) * vec->element_size,
           (vec->size - index - 1) * vec->element_size);
  vec->size--;
}

// Clear all elements from the vector
void
clear (Vector *vec)
{
  vec->size = 0;
}