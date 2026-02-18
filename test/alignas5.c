#include <stdint.h>
#include "test.h"

#define A1 __attribute__((aligned(1024)))
#define A2 __attribute__((aligned(4096)))

int main(void) {
  A2 int x3, y3 A1;
  ASSERT(0, ((uintptr_t)&x3 & 4095));   // must be 4096-aligned
  ASSERT(0, ((uintptr_t)&y3 & 1023));   // must be 1024-aligned
  int A2 x2,  y2 A1;

  ASSERT(0, ((uintptr_t)&x2 & 4095));   // must be 4096-aligned
  ASSERT(0, ((uintptr_t)&y2 & 1023));   // must be 1024-aligned
  //ASSERT(0, ((uintptr_t)&y2 & 4095));   // must NOT require 4096

  int A2 x1;
  int A1 y1;

  ASSERT(0, ((uintptr_t)&x1 & 4095));   // must be 4096-aligned
  ASSERT(0, ((uintptr_t)&y1 & 1023));   // must be 1024-aligned
  //ASSERT(0, ((uintptr_t)&y1 & 4095));   // must NOT require 4096
  A2 int x, y A1;
  ASSERT(0, ((uintptr_t)&x & 4095));   // must be 4096-aligned
  ASSERT(0, ((uintptr_t)&y & 1023));   // must be 1024-aligned
  //ASSERT(0, ((uintptr_t)&y2 & 4095));   // must NOT require 4096
  return 0;
}
