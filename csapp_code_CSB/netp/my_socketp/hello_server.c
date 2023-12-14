// This is the server code
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define clear_mem_region(obj) (memset(&(obj), 0, sizeof(obj)))
#define try(expression) \
  if ((expression) < 0) { \
    perror(#expression " failed"); \
    exit(EXIT_FAILURE); \
  }

int main() {
  
  //**** the comments functions is most improtant execution. others statements
  //just
  // ****collect nessesary data ****

  // socket()
  // create a socket object instance.
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  try(sockfd);

  // bind()
  // OS give the socket FD the local address ADDR
  struct sockaddr_in serv_addr;
  clear_mem_region(serv_addr);
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(7000);
  try(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)));

  // listen()
  try(listen(sockfd, 5));

  // accept()
  struct sockaddr_in cli_addr;
  socklen_t cli_addr_len = sizeof(cli_addr);
  int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
  try(connfd);

  // write()
  char *message = "Hello world!";
  write(connfd, message, strlen(message));
  close(connfd);

  // clear()
  close(sockfd);
  return 0;
}
