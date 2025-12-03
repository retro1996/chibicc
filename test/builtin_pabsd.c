#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = {-100, 200};

    v2si r = __builtin_ia32_pabsd(a);

    int expected[2] = {100,200};

    for(int i=0;i<2;i++)
        ASSERT(expected[i], r[i]);

    printf("PABSD MMX OK\n");
    return 0;
}
