#include "args.h"
#include <stdlib.h>

char *getIterationArg(int argc, char *argv[]) {
   return argc == 2 ? argv[1] : NULL;
}
