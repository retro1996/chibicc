#include "test.h"
#include <stdio.h>

typedef short  v8hi __attribute__((vector_size(16)));
typedef int    v4si __attribute__((vector_size(16)));

int main() {
    // ===== phsubw128 =====
    v8hi a = {1, 2, 3, 4, 5, 6, 7, 8};
    v8hi b = {10, 20, 30, 40, 50, 60, 70, 80};

    // phsubw: subtract adjacent 16-bit elements
    v8hi result_w = __builtin_ia32_phsubw128(a, b);
    // expected: [1-2=-1, 3-4=-1, 5-6=-1, 7-8=-1, 10-20=-10, 30-40=-10, 50-60=-10, 70-80=-10]
    ASSERT(-1, result_w[0]);
    ASSERT(-1, result_w[1]);
    ASSERT(-1, result_w[2]);
    ASSERT(-1, result_w[3]);
    ASSERT(-10, result_w[4]);
    ASSERT(-10, result_w[5]);
    ASSERT(-10, result_w[6]);
    ASSERT(-10, result_w[7]);

    // ===== phsubd128 =====
    v4si c = {100, 200, 300, 400};
    v4si d = {10, 20, 30, 40};

    v4si result_d = __builtin_ia32_phsubd128(c, d);
    // expected: [100-200=-100, 300-400=-100, 10-20=-10, 30-40=-10]
    ASSERT(-100, result_d[0]);
    ASSERT(-100, result_d[1]);
    ASSERT(-10, result_d[2]);
    ASSERT(-10, result_d[3]);

    // ===== phsubsw128 (saturated 16-bit subtraction) =====
    v8hi e = {30000, -30000, 20000, -20000, 10000, -10000, 0, 0};
    v8hi f = {-10000, 10000, -20000, 20000, -30000, 30000, 0, 0};

    v8hi result_sw = __builtin_ia32_phsubsw128(e, f);
    // expected: saturating subtraction
    // [30000-(-30000)=32767, 20000-(-20000)=32767, 10000-(-10000)=32767, 0-0=0,
    //  -10000-10000=-20000, -20000-20000=-32768, 0-0=0, 0-0=0]
    ASSERT(32767, result_sw[0]);
    ASSERT(32767, result_sw[1]);
    ASSERT(20000, result_sw[2]);
    ASSERT(0, result_sw[3]);
    ASSERT(-20000, result_sw[4]);
    ASSERT(-32768, result_sw[5]);
    ASSERT(-32768, result_sw[6]);
    ASSERT(0, result_sw[7]);

    printf("All PHSUB tests OK\n");
    return 0;
}
