#include <stdint.h>
#include "test.h"

typedef struct __attribute__((aligned(32))) {
  char data[17];
} S32;

#define CHECK_ALIGN(ptr, align) \
  ASSERT(0, ((uintptr_t)(ptr)) & ((align) - 1))

static int recur(int depth, S32 s) {
  CHECK_ALIGN(&s, 32);
  ASSERT(3, s.data[0]);

  if (depth == 0)
    return 0;
  return recur(depth - 1, s);
}

int main(void) {
  S32 s = {{3}};
  ASSERT(0, recur(5, s));
  printf("OK\n");
  return 0;
}
