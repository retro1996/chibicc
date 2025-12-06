#include "test.h"


typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = { 100, 200 };
    v2si b = { 10,  20  };

    v2si r = __builtin_ia32_phsubd(a, b);

    ASSERT(-100, r[0]);  // 100 - 200
    ASSERT(-10,  r[1]);  // 10 - 20

    printf("phsubd OK\n");
    return 0;
}
