#include <stdlib.h>


typedef struct point
{
  double x, y, z;
} point_t;

typedef struct 
{
  // number of points in the array
  size_t len;
  
  // pointer to an array of point_t structs
  // There is space for 'allocated' structs, but 
  // 'len' structs have been used so far.
  point_t* points;
  
  // for Task 2, do not use for Task 1
  size_t reserved; 
  
} point_array_t;


/* ALL THESE FUNCTIONS REQUIRE A VALID POINT_ARRAY_T POINTER AS THEIR
   FIRST PARAMETER. THEY SHOULD FAIL ON ASSERTION IF THIS POINTER IS
   NULL */

// Safely initalize an empty array structure.
void point_array_init( point_array_t* pa );

// Resets the array to be empty, freeing any memory allocated if
// necessary.
void point_array_reset( point_array_t* pa );

// Append a point to the end of an array. If successful, return 0,
// else return 1;
int point_array_append( point_array_t* pa, point_t* p );

// Remove the point at index i from the array, reducing the size of
// the array by one. The order of points in the array may change.
// Return 0 on success and 1 on failure.
int point_array_remove( point_array_t* pa, unsigned int i );


