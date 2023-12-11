#include <pthread.h>  // Include the Pthreads header file
#include <stdio.h>
#include <stdlib.h>

#define s2i atoi
// Define a thread function that runs the system function
void *run_client(void *arg) {
  system("./client");  // Your command here
  return NULL;
}

// using 5000 threads is OK~
// 5000 process not OK~ even pretty lag.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./program <count>\n");
    return 1;
  }

  int count = s2i(argv[1]);  // Convert the command-line argument to an integer

  // TODO learn thread apis with thread concepts(back and forth recursive
  // complement each other). and also learn process apis and concepts. Declare
  // an array of thread identifiers
  pthread_t thread_ids[count];

  // Create a thread for each system function call
  for (int i = 0; i < count; i++) {
    pthread_create(&thread_ids[i], NULL, run_client, NULL);
  }

  // Wait for all threads to finish
  for (int i = 0; i < count; i++) {
    pthread_join(thread_ids[i], NULL);
  }

  return 0;
}
