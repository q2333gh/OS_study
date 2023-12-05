#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <syslog.h>
int main() {
// Fork the process and let the parent exit
pid_t pid = fork();

if (pid < 0) {
    exit(EXIT_FAILURE);
}

if (pid > 0) {
    exit(EXIT_SUCCESS);
}

// Create a new session and process group
if (setsid() < 0) {
    exit(EXIT_FAILURE);
}

// Change the working directory to root
if (chdir("/") < 0) {
    exit(EXIT_FAILURE);
}

// Close the standard file descriptors
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

// Open the syslog for logging
openlog("qsr_server_daemon", LOG_PID, LOG_DAEMON);

while (1) {
    // TODO: Insert daemon code here.
    // For example, you can monitor the qsr_server process by using system calls like kill, waitpid, etc.
    // You can also use syslog to log messages, errors, etc.

    // Sleep for 10 seconds
    sleep(10);
}

// Close the syslog
closelog();

return 0;
}