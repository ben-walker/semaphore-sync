/**
 * Ben Walker
 * CIS*3110
 * 
 * Library to retrieve the "number of iterations" argument
 * from argv array.
 */

#include "args.h"
#include <stdlib.h>

/**
 * Retrieve the "number of iterations" (i.e. 2nd) argument from command
 * line parameters and validate the number of parameters.
 */
char *getIterationArg(int argc, char *argv[]) {
   // return the 2nd arg or NULL (if 2 args not supplied)
   return argc == 2 ? argv[1] : NULL;
}
