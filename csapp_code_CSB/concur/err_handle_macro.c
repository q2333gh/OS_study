#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



// TODO is this macro good ? gen by GPT.
// \ is syntax needed in #define macros of multiple line.
#define HANDLE_ERROR(expr)                                        \
  do {                                                            \
    if ((expr) != 0) {                                            \
      fprintf(stderr, "Error at line %d: %s\n", __LINE__, #expr); \
      exit(EXIT_FAILURE);                                         \
    }                                                             \
  } while (0)

void* async_function(void* arg) {
  // Simulate work.
  sleep(2);
  int* result = malloc(sizeof(int));
  *result = 8;
  return result;
}

int main() {
  pthread_t thread;

  // Launch async_function in a separate thread.
  HANDLE_ERROR(pthread_create(&thread, NULL, async_function, NULL));

  // Do other work.

  // Get the result. This will block until the value is ready.
  void* result;
  HANDLE_ERROR(pthread_join(thread, &result));

  printf("Result: %d\n", *(int*)result);
  free(result);

  return 0;
}