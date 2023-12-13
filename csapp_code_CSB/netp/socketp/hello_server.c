// This is the server code
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// also using inline function is ok.
// similar to macros, but they have the advantages of type checking, debugging,
// and namespace.
#define clear_mem_region(obj) (memset(&(obj), 0, sizeof(obj)))

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
  memset(&serv_addr, 0, sizeof(serv_addr));
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

  // accept()
  struct sockaddr_in cli_addr;
  socklen_t cli_addr_len = sizeof(cli_addr);
  int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
  if (connfd < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }
  // write()
  char *message = "Hello world!";
  write(connfd, message, strlen(message));
  close(connfd);

  // clear()
  close(sockfd);
  return 0;
  
}
