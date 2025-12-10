#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {-1000, 2000, -3000, 4000};

    v4hi r = __builtin_ia32_pabsw(a);

    int expected[4] = {1000,2000,3000,4000};

    for(int i=0;i<4;i++)
        ASSERT(expected[i], r[i]);

    printf("PABSW MMX OK\n");
    return 0;
}
