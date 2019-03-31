/**
 * Ben Walker
 * CIS*3110
 * 
 * Iterate a counter, synced between two pthreads using posix semaphores.
 */

#include "fatal.h"
#include "args.h"
#include "numbers.h"
#include "validate.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// `cnt` will be incremented `iter` times for each thread
int cnt = 0, iter;
// the semaphore used to block when a thread is processing
sem_t sema4;

/**
 * Function to be called from within a thread.
 * Increments `cnt` `iter` times.
 * Block other threads using sem_wait() and sem_post().
 */
void *count(void *a) {
   sem_wait(&sema4); // wait for this thread to finish
   int target = cnt + iter; // the new value to increment `cnt` to
   for (; cnt < target; cnt += 1)
      ;
   if (sem_post(&sema4) != 0) // let other threads know we're done
      fatal("sem_post");
   return NULL;
}

/**
 * Simply prints a usage statement to stderr and exits (with failure)
 */
void usageStatement(const char *program) {
   fprintf(stderr, "usage: %s threadIncrementIndex\n", program);
   exit(EXIT_FAILURE);
}

/**
 * Exits all pthreads, destroys and frees semaphore.
 */
void cleanUp() {
   pthread_exit(NULL);
   if (sem_destroy(&sema4) != 0)
      fatal("sem_destroy");
   free(&sema4);
}

/**
 * Creates pthreads, associates them with the count function,
 * and checks that the final `cnt` is consistent after both threads
 * have completed.
 */
int main(int argc, char *argv[]) {
   if (toInt(getIterationArg(argc, argv), &iter) == EXIT_FAILURE)
      usageStatement(argv[0]); // failed to convert the "number of iterations" arg to an int
   if (!isValid(iter))
      usageStatement(argv[0]); // the number of iterations specified is invalid (i.e. < 0)

   if (sem_init(&sema4, 0, 1) != 0) // get the semaphore ready, set its value to 1
      fatal("sem_init");

   // Display the number of times (entered by the user) that each thread
   // increments the shared `cnt`
   /* PLEASE DO NOT remove or modify the following code */
   printf("2*NITER is [%d]\n", 2 * iter);
   /* End of code section */

   pthread_t thread1, thread2;
   /* Thread creation */
   if (pthread_create(&thread1, NULL, count, NULL)) // create thread 1
      fatal("\n ERROR creating thread 1");
   if (pthread_create(&thread2, NULL, count, NULL)) // create thread 2
      fatal("\n ERROR creating thread 2");

   /* Thread execution */
   if(pthread_join(thread1, NULL)) // wait for thread 1 to finish
      fatal("\n ERROR joining thread");
   if(pthread_join(thread2, NULL)) // wait for thread 2 to finish
      fatal("\n ERROR joining thread");

   // Display the value of `cnt`
   /* PLEASE DO NOT remove or modify the following code */
   printf("\nCounter is [%d]\n", cnt);
   if (cnt == 2 * iter)
      printf("\nPASS\n");
   else
      printf("\nFAIL\n");
   /* End of code section */
   cleanUp();
}
