#include "test.h"

typedef long long v2di __attribute__((vector_size(16)));

int main() {
    v2di a = {0xFFLL, 0x0LL};
    v2di b = {0xFFLL, 0x0LL};
    v2di c = {0x0LL, 0xFFLL};
    v2di d = {0xFFLL, 0xFFLL};

    // a & b == b? yes -> 1
    int r1 = __builtin_ia32_ptestc128(a, b);
    ASSERT(1, r1);

    // a & c == c? a&c = {0,0} != c -> 0
    int r2 = __builtin_ia32_ptestc128(a, c);
    ASSERT(0, r2);

    // d & b == b? d&b = {0xFF,0} == b -> 1
    int r3 = __builtin_ia32_ptestc128(d, b);
    ASSERT(1, r3);

    // c & a == a? c&a = {0,0} != a -> 0
    int r4 = __builtin_ia32_ptestc128(c, a);
    ASSERT(0, r4);

    printf("ptestc128 OK\n");
    return 0;
}
