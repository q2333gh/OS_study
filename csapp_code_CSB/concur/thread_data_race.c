#include <pthread.h>
#include <stdio.h>

int result;  // global variable
int thread_num = 4;
int add_round = 10;
int test_round = 10;

void *adder(void *arg) {
  pthread_t tid = *(pthread_t *)arg;
  int last6 = tid % 1000000;

  for (size_t i = 0; i < add_round; i++) {
    result = result + 1;
    printf("thread %lu in computing : %d\n", last6, result);
  }

  pthread_exit(NULL);
}

void thread_run() {
  pthread_t tid;
  //   int arg = 10;
  pthread_create(&tid, NULL, adder, &tid);
  // TODO critical function here: learn the diff of join and not join.
//   pthread_join(tid, NULL);
}

void test_race() {
  result = 0;
  for (size_t i = 0; i < thread_num; i++) {
    thread_run();
  }
  printf("The result is %d\n", result);
}

int main() {
  for (size_t i = 0; i < test_round; i++) {
    test_race();
  }
  printf("right after submit thread to run %d\n", result);

  return 0;
}