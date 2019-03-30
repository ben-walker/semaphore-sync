#include "fatal.h"
#include "args.h"
#include "numbers.h"
#include "validate.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int cnt = 0, iter;
sem_t sema4;

void *count(void *a) {
   sem_wait(&sema4);
   int target = cnt + iter;
   for (; cnt < target; cnt += 1)
      ;
   if (sem_post(&sema4) != 0)
      fatal("sem_post");
   return NULL;
}

void usageStatement(const char *program) {
   fprintf(stderr, "usage: %s threadIncrementIndex\n", program);
   exit(EXIT_FAILURE);
}

void cleanUp() {
   pthread_exit(NULL);
   if (sem_destroy(&sema4) != 0)
      fatal("sem_destroy");
   free(&sema4);
}

int main(int argc, char *argv[]) {
   if (toInt(getIterationArg(argc, argv), &iter) == EXIT_FAILURE)
      usageStatement(argv[0]);
   if (!isValid(iter))
      usageStatement(argv[0]);

   if (sem_init(&sema4, 0, 1) != 0)
      fatal("sem_init");

   // Display the number of times (entered by the user) that each thread
   // increments the shared count cnt
   /* PLEASE DO NOT remove or modify the following code */
   printf("2*NITER is [%d]\n", 2 * iter);
   /* End of code section */

   pthread_t thread1, thread2;
   if (pthread_create(&thread1, NULL, count, NULL)) // create thread 1
      fatal("\n ERROR creating thread 1");
   if (pthread_create(&thread2, NULL, count, NULL)) // create thread 2
      fatal("\n ERROR creating thread 2");

   if(pthread_join(thread1, NULL)) // wait for thread 1 to finish
      fatal("\n ERROR joining thread");
   if(pthread_join(thread2, NULL)) // wait for thread 2 to finish
      fatal("\n ERROR joining thread");

   // Display the value of count cnt
   /* PLEASE DO NOT remove or modify the following code */
   printf("\nCounter is [%d]\n", cnt);
   if (cnt == 2 * iter) 
      printf("\nPASS\n");
   else
      printf("\nFAIL\n");
   /* End of code section */
   cleanUp();
}
