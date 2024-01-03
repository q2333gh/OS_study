#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Allocate 1GB of memory
  size_t size = 10*1024 * 1024 * 1024;  // 1GB
  uint8_t* mem_pool = (uint8_t*)malloc(size);
  if (mem_pool == NULL) {
    printf("Failed to allocate memory pool.\n");
    return 1;
  }

  memset(mem_pool, 0, size);

  // Use the memory pool as needed
  // ...
  while (1) {
    int a = 0;
  }

  // Free the memory pool when you're done
  free(mem_pool);

  return 0;
}