#include "numbers.h"
#include <stdlib.h>
#include <limits.h>

int toInt(const char *val, int *number) {
   if (!val)
      return EXIT_FAILURE;
   char *end = NULL;
   long converted = strtol(val, &end, 0);

   if (converted == LONG_MAX || converted == LONG_MIN || end == val)
      return EXIT_FAILURE;
   *number = converted;
   return EXIT_SUCCESS;
}
