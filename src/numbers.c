/**
 * Ben Walker
 * CIS*3110
 * 
 * Library to convert a string to a number.
 */

#include "numbers.h"
#include <stdlib.h>
#include <limits.h>

/**
 * Convert a string to an integer, put the result in `number`.
 * Returns 0 on success, 1 on failure.
 */
int toInt(const char *val, int *number) {
   if (!val)
      return EXIT_FAILURE;
   char *end = NULL;
   long converted = strtol(val, &end, 0);

   // check for strtol errors
   if (converted == LONG_MAX || converted == LONG_MIN || end == val)
      return EXIT_FAILURE;
   *number = converted;
   return EXIT_SUCCESS;
}
