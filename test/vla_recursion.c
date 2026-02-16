#include "test.h"

static long recurse_vla(int depth, int limit) {
  int n = depth + 3;
  int vla[n];

  for (int i = 0; i < n; i++)
    vla[i] = depth * 100 + i;

  long local_sum = 0;
  for (int i = 0; i < n; i++)
    local_sum += vla[i];

  if (depth == limit)
    return local_sum;

  return local_sum + recurse_vla(depth + 1, limit);
}

int main(void) {
  // Sum over depth d=1..5, each with VLA length d+3 and values d*100+i.
  // Per-depth sums: 406, 1010, 1815, 2821, 4028 => total 10080.
  ASSERT(10080, recurse_vla(1, 5));

  // Slightly deeper recursion to exercise repeated VLA allocation.
  ASSERT(22155, recurse_vla(2, 7));

  return 0;
}
