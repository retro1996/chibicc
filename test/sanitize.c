#include "test.h"

#define NO_SANITIZE(x) __attribute__((__no_sanitize__(x)))

NO_SANITIZE("address")
int f1(int x) { return x; }

NO_SANITIZE(undef)
int f2(int x) { return x; }

int main(void) {
  ASSERT(1, f1(1));
  ASSERT(-1, f2(-1));
  printf("OK\n");
  return 0;
}