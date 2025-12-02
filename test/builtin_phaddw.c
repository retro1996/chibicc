#include "test.h"

typedef short  v4hi __attribute__((vector_size(8)));

int main() {
  // __builtin_ia32_phaddw:
  // For 4 × 16-bit values:
  //   result = [a0+a1, a2+a3, b0+b1, b2+b3]

  v4hi a = {1,  2,  3,  4};
  v4hi b = {10, 20, 30, 40};

  v4hi result = __builtin_ia32_phaddw(a, b);

  printf("%d %d %d %d\n",
         (int)result[0], (int)result[1],
         (int)result[2], (int)result[3]);

  // Expected:
  // a0+a1 = 1+2  = 3
  // a2+a3 = 3+4  = 7
  // b0+b1 = 10+20 = 30
  // b2+b3 = 30+40 = 70

  ASSERT(3,  result[0]);
  ASSERT(7,  result[1]);
  ASSERT(30, result[2]);
  ASSERT(70, result[3]);

  printf("OK\n");
  return 0;
}
