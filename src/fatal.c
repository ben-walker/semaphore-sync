#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>

void fatal(const char *msg) {
   perror(msg);
   exit(EXIT_FAILURE);
}
