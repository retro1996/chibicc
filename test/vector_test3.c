#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <nmmintrin.h>
#include "test.h"


uint32_t 
pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len)
{
	const unsigned char *p = data;
	const unsigned char *pend = p + len;

	/*
	 * Process eight bytes of data at a time.
	 *
	 * NB: We do unaligned accesses here. The Intel architecture allows that,
	 * and performance testing didn't show any performance gain from aligning
	 * the begin address.
	 */
#ifdef __x86_64__
	while (p + 8 <= pend)
	{
		crc = (uint32_t) _mm_crc32_u64(crc, *((const uint64_t *) p));
		p += 8;
	}

	/* Process remaining full four bytes if any */
	if (p + 4 <= pend)
	{
		crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
		p += 4;
	}
#else

	/*
	 * Process four bytes at a time. (The eight byte instruction is not
	 * available on the 32-bit x86 architecture).
	 */
	while (p + 4 <= pend)
	{
		crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
		p += 4;
	}
#endif							/* __x86_64__ */

	/* Process any remaining bytes one at a time. */
	while (p < pend)
	{
		crc = _mm_crc32_u8(crc, *p);
		p++;
	}

	return crc;
}


int main() {
    // Example data
    const char data[] = "This is a test string for CRC32C!";
    size_t tmplength = sizeof(data);
    size_t length = sizeof(data) - 1; // Exclude the null terminator
    printf("length = %ld templength=%ld\n", length, tmplength);
    ASSERT(33, length);
    ASSERT(34, tmplength);

    // Initial CRC value
    uint32_t crc = 0;

    // Compute CRC
    crc = pg_comp_crc32c_sse42(crc, data, length);

    // Print the result
    printf("CRC32C: %08X\n", crc);
    ASSERT(0x2393B78F, crc);

    return 0;
}