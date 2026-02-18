#include <stdint.h>
#include <stdio.h>
#include <nmmintrin.h> // SSE4.2 intrinsics

typedef uint32_t crc32_t;

// SSE4.2 CRC function
__attribute__((target("sse4.2")))
crc32_t crc64_buffer(crc32_t crc, const void *data, size_t len) {
    const uint64_t *p = (const uint64_t *)data;
    const uint64_t *pend = p + len / 8;
    crc32_t r = crc;

    while (p < pend) {
        // <-- pointer dereference triggers segfault if lowering is incorrect
        r = (crc32_t)_mm_crc32_u64(r, *p);
        p++;
    }

    // remaining bytes (optional)
    const uint8_t *q = (const uint8_t *)p;
    size_t rem = len % 8;
    for (size_t i = 0; i < rem; i++) {
        r = _mm_crc32_u8(r, q[i]);
    }

    return r;
}

int main(void) {
    uint64_t buf[2] = {0x1122334455667788ULL, 0x99aabbccddeeff00ULL};
    crc32_t (*fptr)(crc32_t, const void*, size_t);

    // indirect call simulates PostgreSQL runtime dispatch
    fptr = crc64_buffer;

    // This can crash in chibicc if _mm_crc32_u64 is mis-lowered
    crc32_t crc = fptr(0, buf, sizeof(buf));

    printf("CRC = %u\n", crc);
    return 0;
}
