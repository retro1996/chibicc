#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

static __attribute__((noinline)) int from_call(int x) {
    // Explicitly clobber xmm0 so vec-init must preserve prior packed lanes.
    __asm__ volatile("pxor %%xmm0, %%xmm0" ::: "xmm0");
    return x;
}

int main() {
    v4hi v = __builtin_ia32_vec_init_v4hi(1, 2, 3, 4);

    for (int i = 0; i < 4; i++) {
        ASSERT(i+1, v[i]);
    }

    v4hi v2 = __builtin_ia32_vec_init_v4hi(
        from_call(11), from_call(22), from_call(33), from_call(44));
    ASSERT(11, v2[0]);
    ASSERT(22, v2[1]);
    ASSERT(33, v2[2]);
    ASSERT(44, v2[3]);

    return 0;
}
