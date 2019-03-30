#include "fatal.h"
#include "args.h"
#include "numbers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int cnt = 0, iter;

void *Count(void *a) {
   int tmp;
   for (int i = 0; i < iter; i += 1) {
      tmp = cnt; // copy the global cnt locally
      tmp += 1; // increment the local copy
      cnt = tmp; // store the local value into the global cnt
   }
   return NULL;
}

void usageStatement(const char *program) {
	fprintf(stderr, "usage: %s threadIncrementIndex\n", program);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	// validate arguments
	// implementation
	if (toInt(getIterationArg(argc, argv), &iter) == EXIT_FAILURE)
		usageStatement(argv[0]);

	// Parsing the arguments passed to your C program
	// Including the number of times that each thread increments
	// the shared count cnt
	// For example, NITER = 20000;


	// Display the number of times (entered by the user) that each thread
	// increments the shared count cnt
	/* PLEASE DO NOT remove or modify the following code */
	printf("2*NITER is [%d]\n", 2 * iter);
	/* End of code section */

	pthread_t tid1, tid2;

	// creating Thread 1
	if (pthread_create(&tid1, NULL, Count, NULL))
		fatal("\n ERROR creating thread 1");

	// creating Thread 2
	if (pthread_create(&tid2, NULL, Count, NULL))
		fatal("\n ERROR creating thread 2");

	if(pthread_join(tid1, NULL)) // wait for the thread 1 to finish
		fatal("\n ERROR joining thread");

	if(pthread_join(tid2, NULL)) // wait for the thread 2 to finish
		fatal("\n ERROR joining thread");

   // Display the value of count cnt
	/* PLEASE DO NOT remove or modify the following code */
	printf("\nCounter is [%d]\n", cnt);
	if (cnt == 2 * iter) 
		printf("\nPASS\n");
	else
		printf("\nFAIL\n");
	/* End of code section */

	pthread_exit(NULL);
}
