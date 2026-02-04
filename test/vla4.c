// vla_tail_struct_test.c
#include "test.h"
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>


/*
 * Struct with VLA as last member.
 * This is NOT a flexible array member.
 * Size depends on runtime value.
 */
struct VLA {
    uint32_t magic;
    size_t   len;
    __attribute__((aligned(16))) unsigned char data[]; /* ensure alignment stress */
};

/* Allocate a VLA-sized object */
static struct VLA *vla_new(size_t len) {
    size_t size = sizeof(struct VLA) + len;
    struct VLA *p = malloc(size);


    p->magic = 0xDEADBEEF;
    p->len   = len;
    memset(p->data, 0xAA, len);
    ASSERT(1, p != NULL);
    return p;
}

/* Validate layout and contents */
static void vla_check(struct VLA *p) {
    ASSERT(0xDEADBEEF, p->magic);
    ASSERT(0, p->len == 0); // Ensure len is not zero

    for (size_t i = 0; i < p->len; i++) {
        if (p->data[i] != 0xAA) {
            fprintf(stderr, "data corruption at %zu\n", i);
            abort();
        }
    }
}

/* Force pointer arithmetic and alignment checks */
static uint64_t vla_checksum(struct VLA *p) {
    uint64_t sum = 0;
    for (size_t i = 0; i < p->len; i++) {
        sum = (sum << 1) ^ p->data[i];
    }
    return sum;
}

/* Stress nested usage (CPython-like) */
static void stress(void) {
    for (size_t i = 1; i <= 256; i++) {
        struct VLA *p = vla_new(i * 7);
        vla_check(p);

        uint64_t c = vla_checksum(p);
        if (c == 0) {
            fprintf(stderr, "impossible checksum\n");
            abort();
        }

        free(p);
    }
}

int main(void) {
    puts("[VLA tail struct test]");
    printf("sizeof(struct VLA) = %zu\n", sizeof(struct VLA));
    ASSERT(16, sizeof(struct VLA)); // aligned to 16 bytes

    stress();

    puts("OK");
    return 0;
}
