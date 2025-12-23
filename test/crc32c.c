#include <stdint.h>
#include "test.h"
#include <smmintrin.h>

__attribute__((noinline)) uint32_t test_crc32_u8(uint32_t crc, uint8_t v) {
    return _mm_crc32_u8(crc, v);
}


__attribute__((noinline)) uint32_t test_crc32_u16(uint32_t crc, uint16_t v) {
    return _mm_crc32_u16(crc, v);
}


__attribute__((noinline)) uint32_t test_crc32_u32(uint32_t crc, uint32_t v) {
    return _mm_crc32_u32(crc, v);
}



__attribute__((noinline)) uint32_t test_crc32_u64(uint64_t crc, uint64_t v) {
    return _mm_crc32_u64(crc, v);
}


int main(void)
{
    uint32_t c32 = 0;
    uint64_t c64 = 0;

    c32 = test_crc32_u8(c32, 0x12);
    printf("%d\n", c32);
    ASSERT(-244992104, c32);
    c32 = test_crc32_u16(c32, 0x3456);
    printf("%d\n", c32);
    ASSERT(1638504350, c32);
    c32 = test_crc32_u32(c32, 0x789abcde);
    printf("%d\n", c32);
    ASSERT(-2066154244, c32);

    c64 = test_crc32_u64(c64, 0x0123456789abcdefULL);
    printf("%ld\n", c64);
    ASSERT(-375887191, c64);

    return 0;
}