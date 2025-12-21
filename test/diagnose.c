#include "test.h"

#define ATTR_DIAG(_, __, ___) \
  __attribute__((__diagnose_if__(_, __, ___)))

ATTR_DIAG(1, "msg", warning)
int f1(int x);

ATTR_DIAG(x > 0, "x must be positive", error)
int f2(int x);

int f1(int x) { return x; }
int f2(int x) { return x; }
int main(void) {
  f1(1);
  f2(-1); // expected-error {{x must be positive}}
  ASSERT(1, f1(1));
  ASSERT(-1, f2(-1));
  printf("OK\n");
  return 0;
}