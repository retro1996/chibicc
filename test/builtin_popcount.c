#include "test.h"
#include <stdint.h>

int main() {
    // Basic tests
    ASSERT(0, __builtin_popcount(0));
    ASSERT(1, __builtin_popcount(1));
    ASSERT(4, __builtin_popcount(15));
    ASSERT(32, __builtin_popcount(0xffffffff));
    
    // Patterns
    ASSERT(16, __builtin_popcount(0xAAAAAAAA));
    ASSERT(16, __builtin_popcount(0x55555555));

    // long and long long
    ASSERT(0, __builtin_popcountl(0));
    ASSERT(1, __builtin_popcountl(1));
    ASSERT(32, __builtin_popcountl(0xF0F0F0F0F0F0F0F0));
    ASSERT(64, __builtin_popcountll(0xFFFFFFFFFFFFFFFF));
    
    // Promotion tests (crucial for small types)
    unsigned char c = 0xFF;
    ASSERT(8, __builtin_popcount(c));
    
    unsigned short s = 0xFFFF;
    ASSERT(16, __builtin_popcount(s));
    
    // Pattern variables
    uint32_t a32 = 0xF0F0F0F0;
    uint64_t a64 = 0xF0F0F0F0F0F0F0F0;
    
    ASSERT(16, __builtin_popcount(a32));
    ASSERT(32, __builtin_popcountl(a64));
    ASSERT(32, __builtin_popcountll(a64));

    // Mixed expressions
    ASSERT(2, __builtin_popcount(1 | 2));
    ASSERT(4, __builtin_popcountll(a64 & 0xF0));

    printf("OK\n");
    return 0;
}
