#include "test.h"

int main() {
  char flag = 0;
  int ret;

  // Test __atomic_test_and_set
  // 5 is __ATOMIC_SEQ_CST
  ret = __atomic_test_and_set(&flag, 5);
  ASSERT(0, ret);
  ASSERT(1, flag);

  ret = __atomic_test_and_set(&flag, 5);
  ASSERT(1, ret);
  ASSERT(1, flag);

  // Test __atomic_clear
  __atomic_clear(&flag, 5);
  ASSERT(0, flag);

  // Test fences
  __atomic_thread_fence(5);
  __atomic_signal_fence(5);

  printf("OK\n");
  return 0;
}