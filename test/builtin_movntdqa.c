#include "test.h"

typedef long long v2di __attribute__((vector_size(16)));



int main() {
    v2di src = { 0x1122334455667788LL, 0xAABBCCDDEEFF0011LL };

    // Load using movntdqa
    v2di r = __builtin_ia32_movntdqa(&src);

    printf("r[0] = 0x%llx\n", r[0]);
    printf("r[1] = 0x%llx\n", r[1]);

    if (r[0] == src[0] && r[1] == src[1]) {
        printf("movntdqa OK\n");
    } else {
        printf("movntdqa FAIL\n");
    }
    ASSERT(r[0], src[0]);
    ASSERT(r[1], src[1]);
    

    return 0;
}
