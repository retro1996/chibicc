#include "test.h"
#include <stdatomic.h>

int main() {
  atomic_thread_fence(memory_order_seq_cst);
  atomic_signal_fence(memory_order_seq_cst);
  
  atomic_thread_fence(memory_order_acquire);
  atomic_signal_fence(memory_order_release);

  printf("OK\n");
  return 0;
}
