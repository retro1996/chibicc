#include "test.h"

int factorial(int n, int acc) {
  if (n == 0) return acc;
  return factorial(n - 1, acc * n);
}

int sum_many(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int acc) {
  if (a1 == 0) return acc;
  return sum_many(a1 - 1, a2, a3, a4, a5, a6, a7, a8, acc + a1);
}

int main() {
  printf("Test: factorial(10, 1)\n");
  ASSERT(3628800, factorial(10, 1));
  
  printf("Test: sum_many(10, 2, 3, 4, 5, 6, 7, 8, 0)\n");
  ASSERT(55, sum_many(10, 2, 3, 4, 5, 6, 7, 8, 0));
  
  // Test deep recursion to ensure TCO is working (stack overflow if not)
  printf("Test: deep recursion sum_many(1000000, ...)\n");
  ASSERT(1784293664, sum_many(1000000, 2, 3, 4, 5, 6, 7, 8, 0));

  printf("OK\n");
  return 0;
}
