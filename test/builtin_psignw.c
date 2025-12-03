#include "test.h"
#include <stdio.h>

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {1000,-2000,3000,-4000};
    v4hi b = {1,-1,1,-1};

    v4hi r = __builtin_ia32_psignw(a, b);

    int expected[4] = {1000,2000,3000,4000};

    for(int i=0;i<4;i++)
        ASSERT(expected[i], r[i]);

    printf("PSIGNW MMX OK\n");
    return 0;
}
