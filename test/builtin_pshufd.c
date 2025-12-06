#include "test.h"
typedef int v4si __attribute__((vector_size(16)));


static void print_v4si(const char *name, v4si v) {
    printf("%s = {%d, %d, %d, %d}\n", name, v[0], v[1], v[2], v[3]);
}

int main() {
    v4si a = {10, 20, 30, 40};

    // imm8 = 0b 11 10 01 00  = selects elements in normal order
    v4si r0 = __builtin_ia32_pshufd(a, 0b11100100);
    print_v4si("r0", r0);

    // reverse vector: [40, 30, 20, 10]
    v4si r1 = __builtin_ia32_pshufd(a, 0b00011011);
    print_v4si("r1", r1);

    // select {a2, a0, a0, a1}
    // mask bits[1:0]=2, bits[3:2]=0, bits[5:4]=0, bits[7:6]=1
    v4si r2 = __builtin_ia32_pshufd(a, 0b01000010);
    print_v4si("r2", r2);

    ASSERT(10, r0[0]);
    ASSERT(20, r0[1]);
    ASSERT(30, r0[2]);
    ASSERT(40, r0[3]);
    ASSERT(40, r1[0]);
    ASSERT(30, r1[1]);
    ASSERT(20, r1[2]);
    ASSERT(10, r1[3]);
    ASSERT(30, r2[0]);
    ASSERT(10, r2[1]);
    ASSERT(10, r2[2]);
    ASSERT(20, r2[3]);

    printf("pshufd OK\n");
    return 0;
}
