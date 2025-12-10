#include "test.h"

typedef int  v2si __attribute__((vector_size(8)));

int main() {
  // __builtin_ia32_phaddd:
  // For 2 × 32-bit values:
  //   result = [a0+a1, b0+b1]

  v2si a = {100, 200};
  v2si b = {5,   10};

  v2si result = __builtin_ia32_phaddd(a, b);

  printf("%d %d\n", result[0], result[1]);

  // Expected:
  // a0+a1 = 100+200 = 300
  // b0+b1 =  5+10   = 15

  ASSERT(300, result[0]);
  ASSERT(15,  result[1]);

  printf("OK\n");
  return 0;
}
