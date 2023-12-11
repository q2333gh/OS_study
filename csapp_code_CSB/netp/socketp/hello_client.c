// This is the client code
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // socket()
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // connect()
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7000);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("connect failed");
    exit(EXIT_FAILURE);
  }

  // read()
  char buffer[1024];
  int n = read(sockfd, buffer, sizeof(buffer) - 1);
  if (n < 0) {
    perror("read failed");
    exit(EXIT_FAILURE);
  }
  buffer[n] = '\0';
  printf("%s\n", buffer);

  // clear()
  close(sockfd);
  return 0;
}
