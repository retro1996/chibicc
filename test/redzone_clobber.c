#include "test.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <alloca.h>

/*
 * This test stresses expression-temp handling around dynamic stack growth.
 * It is intentionally "freeze_module-like": many small helper calls, lots of
 * stack traffic, and alloca in hot paths.
 */

static uint64_t clobber_with_alloca(int n) {
    int sz = 256 + (n & 127);
    unsigned char *p = (unsigned char *)alloca(sz);
    uint64_t s = 0;

    for (int i = 0; i < sz; i++) {
        p[i] = (unsigned char)(i ^ n);
        s += p[i];
    }

    char fmt[64];
    sprintf(fmt, "alloca:%d:%d", n, sz);
    s += fmt[0];
    return s;
}

static uint64_t clobber_with_malloc(int n) {
    int sz = 256 + (n & 127);
    unsigned char *p = (unsigned char *)malloc((size_t)sz);
    uint64_t s = 0;

    for (int i = 0; i < sz; i++) {
        p[i] = (unsigned char)(i ^ n);
        s += p[i];
    }

    free(p);
    return s + (uint64_t)'a';
}

static uint64_t nested_expr(int a, int b, int c, uint64_t (*fn)(int)) {
    uint64_t t1 = fn(a);
    uint64_t t2 = fn(b);
    uint64_t t3 = fn(c);

    // Force multiple temporaries and calls in one expression.
    return (t1 ^ ((uint64_t)b * 3ULL)) + (t2 & 0x7fffULL) - (t3 % 97ULL);
}

static uint64_t stress_loop(uint64_t (*fn)(int)) {
    uint64_t acc = 0;
    for (int i = 1; i <= 200; i++) {
        int a = i * 13 + 7;
        int b = i * 17 + 11;
        int c = i * 19 + 3;

        // The expression shape here is deliberate.
        acc += nested_expr(a, b, c, fn) + fn(i + 5) - (uint64_t)(a ^ c);
    }
    return acc;
}

int main() {
    uint64_t v_alloca_1 = stress_loop(clobber_with_alloca);
    uint64_t v_alloca_2 = stress_loop(clobber_with_alloca);
    uint64_t v_ref = stress_loop(clobber_with_malloc);

    // Deterministic behavior check: same program path must match exactly.
    LASSERT((long long)v_alloca_1, (long long)v_alloca_2);
    LASSERT((long long)v_ref, (long long)v_alloca_1);
    printf("OK redzone/alloca stress: %llu\n",
           (unsigned long long)v_alloca_1);
    return 0;
}
