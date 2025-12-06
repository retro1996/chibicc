#include "test.h"


typedef short v8hi __attribute__((vector_size(16)));

int main() {
    v8hi a = {1000,-2000,3000,-4000,5000,-6000,7000,-8000};
    v8hi b = {1,-1,1,-1,1,-1,1,-1};

    v8hi r = __builtin_ia32_psignw128(a, b);

    int expected[8] = {1000,2000,3000,4000,5000,6000,7000,8000};

    for (int i=0;i<8;i++)
        ASSERT(expected[i], r[i]);

    printf("PSIGNW128 OK\n");
    return 0;
}
