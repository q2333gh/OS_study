// This is the server code
#include <netinet/in.h>
#include <pthread.h>  // Include the Pthreads header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
// also using inline function is ok.
// similar to macros, but they have the advantages of type checking, debugging,
// and namespace.
#define clear_mem_region(obj) (memset(&(obj), 0, sizeof(obj)))

// Declare a global variable for the client counter
int client_count = 0;

// Declare a global mutex for the counter variable
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

// This is the thread function
void *Hello(void *arg) {
  int connfd = (int)arg;  // Cast the argument to int
  // write()
  char *message = "Hello world!";
  write(connfd, message, strlen(message));
  close(connfd);
  // return NULL
  return NULL;
}

// when server receive each client call. new a thread.
// TODO a threa-pool maybe faster
// TODO profiler. throughtput
// TODO how do using OS-shchdule to keep this running in heavy load threads and
// user shell still response most privilaged?
int main() {
  // socket()
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }
  // bind()
  struct sockaddr_in serv_addr;
  clear_mem_region(serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(7000);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // listen()
  if (listen(sockfd, 5) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  // loop
  // TODO why while(1) here . when not receiving new client calls . will not
  // cause CPU runing 100%?
  while (1) {
    // accept()
    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
    if (connfd < 0) {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }
    // create a thread
    pthread_t thread_id;  // Declare a thread identifier
    pthread_create(
        &thread_id, NULL, Hello,
        (void *)connfd);  // Create a thread that runs the Hello function with
                          // the connected socket as argument
    // detach the thread
    pthread_detach(
        thread_id);  // Detach the thread so that it can run independently and
                     // release its resources when it finishes

    //   TODO how slower will this lock causing speed?  wrap this  below  into a
    //   function and testing it .
    // lock the mutex
    pthread_mutex_lock(
        &count_mutex);  // Lock the mutex to protect the counter variable
    // increment the counter
    client_count++;  // Increment the counter by one
    // print the counter
    printf("Number of clients: %d\n",
           client_count);  // Print the counter value to the terminal
    // unlock the mutex
    pthread_mutex_unlock(
        &count_mutex);  // Unlock the mutex to allow other threads to access the
                        // counter variable
    // return to the loop
  }

  // clear()
  close(sockfd);
  return 0;
}
