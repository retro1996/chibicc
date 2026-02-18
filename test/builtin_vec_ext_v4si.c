#include "test.h"

typedef int int4 __attribute__((vector_size(16)));

int main(void) {
    int4 v = {10, 20, 30, 40};

    int a0 = __builtin_ia32_vec_ext_v4si(v, 0);
    int a1 = __builtin_ia32_vec_ext_v4si(v, 1);
    int a2 = __builtin_ia32_vec_ext_v4si(v, 2);
    int a3 = __builtin_ia32_vec_ext_v4si(v, 3);

    ASSERT(10, a0);
    ASSERT(20, a1);
    ASSERT(30, a2);
    ASSERT(40, a3);

    // Repeat a non-zero lane extraction to catch hidden static-state regressions.
    ASSERT(20, __builtin_ia32_vec_ext_v4si(v, 1));
    ASSERT(20, __builtin_ia32_vec_ext_v4si(v, 1));

    // Dynamic index path.
    int idx = 2;
    ASSERT(30, __builtin_ia32_vec_ext_v4si(v, idx));

    printf("%d %d %d %d\n", a0, a1, a2, a3);
    return 0;
}
