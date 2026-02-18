#include "test.h"

int main(void) {
  _Bool x, y ,b;
  b = 0;
  x = b, y = b--;
  ASSERT(0, x);
  printf("y=%d\n",y);
  ASSERT(0, y);
  x = b, y = b--;
  ASSERT(1, x);
  ASSERT(1, y);
  x = b, y = b--;
  ASSERT(0, x);
  ASSERT(0, y);

  b = 0;
  x = b, y = b++;
  ASSERT(0, x);
  ASSERT(0, y);
  x = b, y = b++;
  ASSERT(1, x);
  ASSERT(1, y);
  x = b, y = b++;
  ASSERT(1, x);
  ASSERT(1, y);

  printf("OK\n");
}