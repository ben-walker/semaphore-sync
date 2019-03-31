/**
 * Ben Walker
 * CIS*3110
 * 
 * Library to report a fatal error and exit the program.
 */

#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Simply perrors and exits (with failure). To be called after
 * a fatal function call that sets errno.
 */
void fatal(const char *msg) {
   perror(msg);
   exit(EXIT_FAILURE);
}
