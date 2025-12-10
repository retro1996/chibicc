#include "test.h"

typedef int s32;
typedef short s16;

typedef s32 v4si __attribute__((vector_size(16))); // 4 × 32-bit
typedef s16 v8hi __attribute__((vector_size(16))); // 8 × 16-bit



int main() {
    v4si a = {1000, 70000, -5, 40000};
    v4si b = {30000, -1000, 50000, 2000};
    
    v8hi r = __builtin_ia32_packusdw128(a, b);
    
    for (int i = 0; i < 8; i++)
        printf("%d ", r[i]);
    printf("\n");
    
    // Expected: 
    // a0=1000 -> 1000
    // a1=70000 -> 65535 (saturation)
    // a2=-5 -> 0 (saturation)
    // a3=40000 -> 40000
    // b0=30000 -> 30000
    // b1=-1000 -> 0
    // b2=50000 -> 65535
    // b3=2000 -> 2000
    ASSERT(1000, r[0]);
    ASSERT(-1, r[1]);
    ASSERT(0, r[2]);
    ASSERT(-25536, r[3]);
    ASSERT(30000, r[4]);
    ASSERT(0, r[5]);
    ASSERT(-15536, r[6]);
    ASSERT(2000, r[7]);
    printf("packusdw128 OK\n");

    return 0;
}
