#include "test.h"

int main() {
    char buffer[64];
    
    // Prefetch the first 32 bytes of buffer into cache
    __builtin_prefetch(buffer, 0, 3);

    // Write some data to buffer
    for (int i = 0; i < 32; i++) {
        buffer[i] = (char)i;
    }

    // Read and sum to check correctness
    int sum = 0;
    for (int i = 0; i < 32; i++) {
        sum += buffer[i];
    }

    printf("Sum = %d\n", sum);
    ASSERT(496, sum);
    return 0;
}
