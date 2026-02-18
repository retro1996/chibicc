#include "test.h"

typedef int v4si __attribute__((vector_size(16)));
typedef int v8si __attribute__((vector_size(32)));


/*
 * 2-argument form:
 *   __builtin_shuffle(a, mask)
 * → normalized to (a, a, mask)
 */
int test_shuffle_2args(void) {
  v4si a = { 10, 20, 30, 40 };
  v4si mask = { 3, 2, 1, 0 };

  v4si r = __builtin_shuffle(a, mask);
  
  ASSERT(40, r[0]);
  ASSERT(30, r[1]);
  ASSERT(20, r[2]);
  ASSERT(10, r[3]);
  return 0;
}

/*
 * 3-argument form:
 *   __builtin_shuffle(a, b, mask)
 */
int test_shuffle_3args(void) {
  v4si a = { 1, 2, 3, 4 };
  v4si b = { 5, 6, 7, 8 };
  v4si mask = { 0, 5, 2, 7 };

  v4si r = __builtin_shuffle(a, b, mask);

  ASSERT(1, r[0]);
  ASSERT(6, r[1]);
  ASSERT(3, r[2]);
  ASSERT(8, r[3]);
  return 0;
}

int main(void) {
  if (test_shuffle_2args())
    return 1;

  if (test_shuffle_3args())
    return 1;

  printf("OK\n");
  return 0;
}
