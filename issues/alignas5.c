#include <stdint.h>
#include "test.h"

#define A1 __attribute__((aligned(1024)))
#define A2 __attribute__((aligned(4096)))

int main(void) {
  A2 int x, y A1;

  ASSERT(0, ((uintptr_t)&x & 4095));   // must be 4096-aligned
  ASSERT(0, ((uintptr_t)&y & 1023));   // must be 1024-aligned
  ASSERT(0, ((uintptr_t)&y & 4095));   // must NOT require 4096

  return 0;
}
