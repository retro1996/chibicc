//#include <smmintrin.h>
#include <stdint.h>
#include "test.h"
typedef unsigned int __v4su __attribute__ ((__vector_size__ (16)));

typedef uint32_t crc32_t;

/* Define the default attributes for the functions in this file. */
#define __DEFAULT_FN_ATTRS                                                     \
  __attribute__((__always_inline__, __nodebug__,                               \
                 __target__("ssse3,no-evex512"), __min_vector_width__(64)))
#define __DEFAULT_FN_ATTRS_MMX                                                 \
  __attribute__((__always_inline__, __nodebug__,                               \
                 __target__("mmx,ssse3,no-evex512"),                           \
                 __min_vector_width__(64)))


#define __DEFAULT_FN_ATTRS                                                     \
  __attribute__((__always_inline__, __nodebug__, __target__("crc32")))


static __inline__ unsigned long long __DEFAULT_FN_ATTRS
_mm_crc32_u64(unsigned long long __C, unsigned long long __D)
{
  return __builtin_ia32_crc32di(__C, __D);
}

// Function marked with target attribute
__attribute__((target("sse4.2")))
crc32_t my_crc(crc32_t crc, const void *data, size_t len) {
    const uint64_t *p = (const uint64_t *)data;
    const uint64_t *end = p + len / 8;

    crc32_t r = crc;
    while (p < end) {
        r = (crc32_t)_mm_crc32_u64(r, *p);  // SSE4.2 intrinsic
        p++;
    }
    return r;
}

int main(void) {
    crc32_t (*crc_func)(crc32_t, const void*, size_t);

    // Call via function pointer (indirect call)
    crc_func = my_crc;

    uint64_t buf[2] = {0x1122334455667788ULL, 0x99aabbccddeeff00ULL};

    // This may crash in chibicc if attribute is ignored
    crc32_t crc = crc_func(0, buf, sizeof(buf));

    printf("CRC = %u\n", crc);
    ASSERT(1848164294, crc);
    return 0;
}
