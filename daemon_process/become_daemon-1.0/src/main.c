#include "../config.h"

// file main.c
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "become_daemon.h"

int
main(int argc, char *argv[])
{
  int ret;
  const char *LOGNAME = "DAEMON_EXAMPLE";

  // turn this process into a daemon
  ret = become_daemon(0);
  if(ret)
  {
    syslog(LOG_USER | LOG_ERR, "error starting");
    closelog();
    return EXIT_FAILURE;
  }

  // we are now a daemon!
  // printf now will go to /dev/null

  // open up the system log
  openlog(LOGNAME, LOG_PID, LOG_USER);
  syslog(LOG_USER | LOG_INFO, "starting");

  // run forever in the background
  while(1)
  {
    sleep(60);
    syslog(LOG_USER | LOG_INFO, "running");
  }

  return EXIT_SUCCESS;
}
