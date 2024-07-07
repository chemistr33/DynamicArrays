/**
 * Dynamic Array (Vector) Implementation
 * Began 6/9/2024
 * Lead Developer: B3N $T^CK5
 * Co-Developers:
 *    GPT-4o
 *    GitHub CoPilot
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef vector__h__
#define vector__h__

/**
 * typedefs
 *
 */

// fpointer for printing elements
typedef void (*print_fptr) (void *);

// fpointer for sort comparison function
typedef int (*compare_fptr) (const void *, const void *);

// fpointer for search comparison function
typedef void (*search_fptr) (void *);

/**
 * Vector Data Structure
 */
typedef struct
{
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
  print_fptr user_print_fn;
  compare_fptr user_sort_compare_fn;
  search_fptr user_search_compare_fn;
} Vector;

/**
 *  ###########################                     ###########################
 *  ########################### Function Prototypes ###########################
 *  ###########################                     ###########################
 */

/**
 *  Callback Registration
 *
 */

// Register LibUser Print Function
void register_user_print_fn (Vector *vec, print_fptr user_print_fn);

// Register LibUser Sort Function, Option 1
void register_user_sort_comparison_fn (Vector *vec,
                                       compare_fptr user_sort_compare_fn);

// Register LibUser Search Function, Option 1
void register_user_search_comparison_fn (Vector *vec,
                                         search_fptr user_search_compare_fn);

/**
 * Callback Functions
 *
 */

// Library print callback function
void printVector (Vector *vec, const char *label);

// Library sort callback function
void sortVector (Vector *vec, size_t left, size_t right);

// Library search callback function
void searchVector (Vector *vec, search_fptr user_search_compare_fn);

/**
 * Init. & Destroy
 */

// Inits new vector
void init_vector (Vector *vec, size_t elem_size);

// Destroys vector
void free_vector (Vector *vec);

/**
 * Capacity Management
 */

// Returns number of elements being used in vector
size_t size (Vector *vec);

// Returns number of elements the vector could hold w/o a resize operation
size_t capacity (Vector *vec);

// Resizes the vector to specified size, reallocates as necessary with
// reserve()
void resize (Vector *vec, size_t new_size);

// Ensures vector capacity is >= specified capacity
void reserve (Vector *vec, size_t new_capacity);

// Reduces capacity to fit the current size (reminder, size = elements in use)
void shrink_to_fit (Vector *vec);

/**
 * Element Access
 */

// Accesses element at specific index
void *at (Vector *vec, size_t index);

// Returns first element (index 0)
void *front (Vector *vec);

// Returns last element (index size - 1)
void *back (Vector *vec);

// Returns pointer to the underlying array
void *data (Vector *vec);

/**
 * Element Modification
 */

// Adds element to the front of the vector
void push (Vector *vec, void *value);

// Adds element to end of vector, reallocating as necessary
void push_back (Vector *vec, void *value);

// Pops element off the front of the vector
void pop (Vector *vec);

// Removes last element
void pop_back (Vector *vec);

// Inserts element at specified index & shifts subsequent elements towards end
void insert (Vector *vec, size_t index, void *value);

// Alters element at specified index
void alterElement (Vector *vec, size_t index, void *value);

// Removes element at specified index & shifts subsequent elements towards
// begin
void erase (Vector *vec, size_t index);

// Clears all elements of the vector
void clear (Vector *vec);

/**
 *  ################################ MACROS ###################################
 */

// Allocation Error-Check Macro MEMCHECK
#define MEMCHECK(ptr)                                                         \
  do                                                                          \
    {                                                                         \
      if (!(ptr))                                                             \
        {                                                                     \
          fprintf (stderr, "MEMCHECK_macro: Allocation Failed.\n");           \
          exit (EXIT_FAILURE);                                                \
        }                                                                     \
    }                                                                         \
  while (0)

// Vector Null-Check
#define NULLCHECK(vec)                                                        \
  do                                                                          \
    {                                                                         \
      if (!(vec))                                                             \
        {                                                                     \
          fprintf (stderr, "NULLCHECK_macro: Vector Null.\n");                \
          exit (EXIT_FAILURE);                                                \
        }                                                                     \
    }                                                                         \
  while (0)

#endif
