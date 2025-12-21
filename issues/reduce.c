#include "test.h"


typedef int __v4si __attribute__((vector_size(16)));
typedef int __v8si __attribute__((vector_size(32)));
typedef long long __m256i __attribute__((vector_size(32)));

int reduce(__v8si __A) {
#define __MM512_REDUCE_OP(op)                                      \
  __v8si __T1 = __A;                                               \
  __v8si __T2 = __A;                                               \
  __m256i __T3 = (__m256i) (__T1 op __T2);                         \
  __v4si __T4 = (__v4si) __T3;                                    \
  __v4si __T5 = (__v4si) __T3;                                    \
  __v4si __T6 = __T4 op __T5;                                     \
  __v4si __T7 = __builtin_shuffle(__T6, (__v4si){2,3,0,1});      \
  __v4si __T8 = __T6 op __T7;                                     \
  return __T8[0] op __T8[1];

  __MM512_REDUCE_OP(+)
}

int main(void) {
    __v8si a = {1,2,3,4,5,6,7,8};
    int r = reduce(a);
    ASSERT(r, 36);
    printf("OK\n");
    return 0;
}   