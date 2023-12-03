// file become_daemon.c
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "become_daemon.h"

int // returns 0 on success -1 on error
become_daemon(int flags)
{
  int maxfd, fd;

  /* the first fork will change our pid
   * but the sid and pgid will be the
   * calling process
   */
  switch(fork())                    // become background process
  {
    case -1: return -1;
    case 0: break;                  // child falls through
    default: _exit(EXIT_SUCCESS);   // parent terminates
  }

  /* we'll become a session leader which
   * allows us to take controler of a tty.
   * Only a session leader can take control
   * of a tty.
   */
  if(setsid() == -1)                // become leader of new session
    return -1;

  /* the magical double fork. We're the session
   * leader from the code above. Since only the
   * session leader can take control of a tty
   * we will fork and exit the session leader.
   * Once the fork is done below and we use
   * the child process we will ensure we're
   * not the session leader, thus, we cannot
   * take control of a tty.
   */
  switch(fork())
  {
    case -1: return -1;
    case 0: break;                  // child breaks out of case
    default: _exit(EXIT_SUCCESS);   // parent process will exit
  }

  if(!(flags & BD_NO_UMASK0))
    umask(0);                       // clear file creation mode mask

  if(!(flags & BD_NO_CHDIR))
    chdir("/");                     // change to root directory

  if(!(flags & BD_NO_CLOSE_FILES))  // close all open files
  {
    maxfd = sysconf(_SC_OPEN_MAX);
    if(maxfd == -1)
      maxfd = BD_MAX_CLOSE;         // if we don't know then guess
    for(fd = 0; fd < maxfd; fd++)
      close(fd);
  }

  if(!(flags & BD_NO_REOPEN_STD_FDS))
  {
    /* now time to go "dark"!
     * we'll close stdin
     * then we'll point stdout and stderr
     * to /dev/null
     */
    close(STDIN_FILENO);

    fd = open("/dev/null", O_RDWR);
    if(fd != STDIN_FILENO)
      return -1;
    if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
      return -2;
    if(dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
      return -3;
  }

  return 0;
}
