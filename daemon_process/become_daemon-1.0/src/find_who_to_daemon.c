#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"

#define MAX_BUFFER_SIZE 128

int findProcessID(const char* programName) {
  FILE* pipe;
  char buffer[MAX_BUFFER_SIZE];
  char command[MAX_BUFFER_SIZE];
  int pid = -1;

  // Construct the command to find the process ID
  snprintf(command, sizeof(command), "pgrep %s", programName);

  // Open the command for reading
  pipe = popen(command, "r");
  if (pipe == NULL) {
    printf("Failed to execute the command.\n");
    return -1;
  }

  // Read the output of the command
  if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    // Parse the PID from the output
    pid = atoi(buffer);
  }

  // Close the pipe and check for errors
  if (pclose(pipe) != 0) {
    printf("Error while closing the pipe.\n");
    return -1;
  }

  return pid;
}

bool run_find(const char* program_name) {
  int pid = findProcessID(program_name);
  if (pid != -1) {
    return false;
  } 
  return true;
}