#include "test.h"
#include <stdint.h>

typedef char v8qi __attribute__((vector_size(8)));

static __attribute__((noinline)) int from_call(int x) {
    // Explicitly clobber xmm0 so vec-init must preserve prior packed lanes.
    __asm__ volatile("pxor %%xmm0, %%xmm0" ::: "xmm0");
    return x;
}

int main() {
    // Test with immediate values
    v8qi v = (v8qi)__builtin_ia32_vec_init_v8qi(
        1, 2, 3, 4, -1, -2, -3, -4
    );

    ASSERT(1, v[0]);
    ASSERT(2, v[1]);
    ASSERT(3, v[2]);
    ASSERT(4, v[3]);
    ASSERT(-1, v[4]);
    ASSERT(-2, v[5]);
    ASSERT(-3, v[6]);
    ASSERT(-4, v[7]);

    // Test with variables
    char a0 = 10, a1 = 20, a2 = 30, a3 = 40;
    char a4 = -10, a5 = -20, a6 = -30, a7 = -40;

    v8qi v2 = (v8qi)__builtin_ia32_vec_init_v8qi(
        a0, a1, a2, a3, a4, a5, a6, a7
    );

    ASSERT(10, v2[0]);
    ASSERT(20, v2[1]);
    ASSERT(30, v2[2]);
    ASSERT(40, v2[3]);
    ASSERT(-10, v2[4]);
    ASSERT(-20, v2[5]);
    ASSERT(-30, v2[6]);
    ASSERT(-40, v2[7]);

    v8qi v3 = (v8qi)__builtin_ia32_vec_init_v8qi(
        from_call(11), from_call(22), from_call(33), from_call(44),
        from_call(-11), from_call(-22), from_call(-33), from_call(-44)
    );
    ASSERT(11, v3[0]);
    ASSERT(22, v3[1]);
    ASSERT(33, v3[2]);
    ASSERT(44, v3[3]);
    ASSERT(-11, v3[4]);
    ASSERT(-22, v3[5]);
    ASSERT(-33, v3[6]);
    ASSERT(-44, v3[7]);

    return 0;
}
