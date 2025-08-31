#include "test.h"
#include <string.h>

int main(void) {
    char buf1[16];
    char buf2[16];

    // --- Direct call: should trigger ND_BUILTIN_MEMSET inline ---
    __builtin_memset(buf1, 'A', sizeof(buf1));

    // Print to verify
    for (int i = 0; i < sizeof(buf1); i++)
        putchar(buf1[i]);
    putchar('\n');

    // --- Indirect call via function pointer: should use alias to libc memset ---
    void *(*ptr)(void *, int, size_t) = memset;
    ptr(buf2, 'B', sizeof(buf2));

    for (int i = 0; i < sizeof(buf2); i++)
        putchar(buf2[i]);
    putchar('\n');

    // Verify return value
    if (ptr(buf2, 'C', 5) == buf2)
        printf("Return value correct!\n");

    ASSERT(1, ptr(buf2, 'C', 5) == buf2);

    return 0;
}
