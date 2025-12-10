#include "test.h"


typedef int v4si __attribute__((vector_size(16)));

int main() {
    v4si a = {-100, 200, -300, 400};

    v4si r = __builtin_ia32_pabsd128(a);

    int expected[4] = {100,200,300,400};

    for(int i=0;i<4;i++)
        ASSERT(expected[i], r[i]);

    printf("PABSD128 OK\n");
    return 0;
}
