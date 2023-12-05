/* $begin dd2hex */
#include "dd2hex.h"

#include "csapp.h"

// #include "../include/csapp.h"
// #include "../src/csapp.c"

int main(int argc, char **argv) {
  check_arg(argc, argv);

  // rc: return code
  struct in_addr inaddr; /* Address in network byte order */
  int rc = inet_pton(AF_INET, argv[1], &inaddr);
  check_rc(rc);

  printf("0x%x\n", ntohl(inaddr.s_addr));
  exit(0);
}

void check_rc(int rc) {
  if (rc == 0)
    app_error("inet_pton error: invalid dotted-decimal address");
  else if (rc < 0)
    unix_error("inet_pton error");
}

void check_arg(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <dotted-decimal>\n", argv[0]);
    exit(0);
  }
}

/* $end dd2hex */