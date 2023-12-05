#include "../config.h"

// file main.c
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "become_daemon.h"
#include "find_who_to_daemon.c"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
  int ret;
  const char *LOGNAME = "DAEMON_EXAMPLE";

  // turn this process into a daemon, means if qsr_server_daemon died. os will auto rerun it .
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
    // find the qsr_server pid.
    // find the process pid when i exec : another program :   ./qsr_server pid
    // using C code
    bool running_status = run_find("qsr_server");
    // if qsr_server not running.  run it .

    if (running_status==false) {
      // run qsr_server and make sure it is running
      // using cwd in qsr_server source code to get qsr_server path .
      // and log the reboot info of qsr_server
      // qsr_server is not running, so we need to start it
      pid_t child_pid = fork();
      if (child_pid == -1) {
        // Error occurred while forking
        syslog(LOG_USER | LOG_ERR, "Error forking to start qsr_server");
      } else if (child_pid == 0) {
        // Child process
        // Execute qsr_server program ;!!! need to set qsr_server as ENV viariable.
        execlp("qsr_server_x86", "qsr_server_x86", NULL);
        // If execlp returns, an error occurred
        syslog(LOG_USER | LOG_ERR, "Error executing qsr_server");
        exit(EXIT_FAILURE);
      } else {
        // Parent process
        // Wait for the child process to exit if necessary
        // You can add code here to handle the child process termination if
        // needed
      }
    }
    int debug_time = 3;
    int product_time = 60;
    sleep(debug_time);
    syslog(LOG_USER | LOG_INFO, "running");
  }

  return EXIT_SUCCESS;
}
