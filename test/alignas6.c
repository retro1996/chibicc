#include <stdio.h>
#include <stdint.h>
#include "test.h"


#define CHECK_ALIGN(ptr, align) \
    do { \
        uintptr_t addr = (uintptr_t)(ptr); \
        if (addr % (align) != 0) { \
            printf("Alignment error: %s at %p not aligned to %d\n", #ptr, (void*)addr, align); \
        } \
        ASSERT(0, addr % (align)); \
    } while(0)
    
#define A1 __attribute__((aligned(1024)))
#define A2 __attribute__((aligned(4096)))
#define A3 __attribute__((aligned(512)))

int main(void) {
    // Attribute before the type
    _Alignas(64) int a;
    A1 int b;

    // Attribute after the type but before the variable
    int _Alignas(128) c;
    int A2 d;

    // Attribute after the variable name
    int e __attribute__((aligned(256)));
    int f A3;

    // Multiple declarators, different alignments
    A2 int x, y A1, z __attribute__((aligned(512)));

    // Check alignments
    CHECK_ALIGN(&a, 64);
    CHECK_ALIGN(&b, 1024);

    CHECK_ALIGN(&c, 128);
    CHECK_ALIGN(&d, 4096);

    CHECK_ALIGN(&e, 256);
    CHECK_ALIGN(&f, 512);

    CHECK_ALIGN(&x, 4096);
    CHECK_ALIGN(&y, 1024);
    CHECK_ALIGN(&z, 512);

    printf("All alignment checks passed!\n");
    return 0;
}
