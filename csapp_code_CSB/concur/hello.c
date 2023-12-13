/*
 * hello.c - Pthreads "hello, world" program
 */
/* $begin hello */
#include "../include/csapp.h"
void *thread(void *vargp);  // line:conc:hello:prototype
struct thread_para {
  int a;
  char b[32];
};

long thread_return;
int main() {  
      // line:conc:hello:main
  pthread_t tid;  // line:conc:hello:tid
  struct thread_para my_para;
  my_para.a = 2;
  strcpy(my_para.b, "Hello, thread!");

  //   after create. the thread will immeadiately start to run.
  // so actually 2 state machine start to run.
  pthread_create(&tid, NULL, thread,
                 (void *)&my_para);  // line:conc:hello:create
  //   wait(telling the caller to block )for thread to finishing job.
  // TODO why we call this behavoir `join` ? how to explain join here ?
  pthread_join(tid, &thread_return);  // line:conc:hello:join
  printf("Thread returned: %ld\n", (long)thread_return);

  exit(0);  // line:conc:hello:exit
}

void *thread(void *vargp) { /* thread routine */  // line:conc:hello:beginthread

  struct thread_para *my_para = (struct thread_para *)vargp;
  printf("Received parameters: a = %d, b = %s\n", my_para->a, my_para->b);
  printf("Hello, world!\nand simulating exec 3 seconds of computation\n");
  sleep(3);
  long thread_return = my_para->a * 10;  // Example return value
  return (void *)thread_return;          // line:conc:hello:return
}  // line:conc:hello:endthread
/* $end hello */
