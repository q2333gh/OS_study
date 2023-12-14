#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHSIZE 100

int main(void) {
  int shmid;
  key_t key;
  char *shm;
  char *s;

  key = 9876;

  shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
  if (shmid < 0) {
    perror("shmget");
    return 1;
  }

  shm = shmat(shmid, NULL, 0);

  if (shm == (char *)-1) {
    perror("shmat");
    return 1;
  }

  pid_t pid = fork();

  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }

  if (pid > 0) { /* parent process */
    char str[] = "shared mem: Hello from Process A!";

    /* Process A writing to the shared memory */
    memcpy(shm, str, strlen(str));

    /* Wait for Process B */
    sleep(2);
  } else { /* child process */
    /* Process B reading from the shared memory */
    for (s = shm; *s != 0; s++) printf("%c", *s);
    printf("\n");
  }

  return 0;
}
