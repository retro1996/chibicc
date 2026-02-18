#include "test.h"

typedef int v2si __attribute__((vector_size(8))); // 2 × 4 bytes = 8 bytes

// Prototype for the builtin so the compiler doesn't warn
v2si __builtin_ia32_vec_init_v2si(int, int);

static __attribute__((noinline)) int rhs_many_args(int a, int b, int c, int d, int e, int f) {
    // Forces use of caller-saved GP registers during rhs evaluation.
    return a + b + c + d + e + f;
}

int main(void) {
    // Basic immediate smoke test.
    v2si v = __builtin_ia32_vec_init_v2si(123456, 0);
    int *p = (int *)&v;
    ASSERT(123456, p[0]);
    ASSERT(0, p[1]);

    // Clobber-sensitive case: lhs must survive rhs function call.
    v2si v2 = __builtin_ia32_vec_init_v2si(0x13579bdf, rhs_many_args(1, 2, 3, 4, 5, 6));
    int *q = (int *)&v2;
    ASSERT(0x13579bdf, q[0]);
    ASSERT(21, q[1]);

    return 0;
}
