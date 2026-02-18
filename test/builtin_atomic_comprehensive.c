#include "test.h"
#include <stdbool.h>

// GCC/Clang atomic memory models
#define __ATOMIC_RELAXED 0
#define __ATOMIC_CONSUME 1
#define __ATOMIC_ACQUIRE 2
#define __ATOMIC_RELEASE 3
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_SEQ_CST 5

void test_int_variants() {
    int x = 100;
    int r;

    // fetch_add
    r = __atomic_fetch_add(&x, 10, __ATOMIC_SEQ_CST);
    ASSERT(100, r);
    ASSERT(110, x);

    // add_fetch
    r = __atomic_add_fetch(&x, 10, __ATOMIC_SEQ_CST);
    ASSERT(120, r);
    ASSERT(120, x);

    // fetch_sub
    r = __atomic_fetch_sub(&x, 20, __ATOMIC_SEQ_CST);
    ASSERT(120, r);
    ASSERT(100, x);

    // sub_fetch
    r = __atomic_sub_fetch(&x, 20, __ATOMIC_SEQ_CST);
    ASSERT(80, r);
    ASSERT(80, x);

    // fetch_and
    r = __atomic_fetch_and(&x, 0xF0, __ATOMIC_SEQ_CST);
    ASSERT(80, r);
    ASSERT(80, x);

    // and_fetch
    x = 0xFF;
    r = __atomic_and_fetch(&x, 0x0F, __ATOMIC_SEQ_CST);
    ASSERT(0x0F, r);
    ASSERT(0x0F, x);

    // fetch_or
    x = 1;
    r = __atomic_fetch_or(&x, 2, __ATOMIC_SEQ_CST);
    ASSERT(1, r);
    ASSERT(3, x);

    // or_fetch
    x = 1;
    r = __atomic_or_fetch(&x, 2, __ATOMIC_SEQ_CST);
    ASSERT(3, r);
    ASSERT(3, x);

    // fetch_xor
    x = 1;
    r = __atomic_fetch_xor(&x, 3, __ATOMIC_SEQ_CST);
    ASSERT(1, r);
    ASSERT(2, x);

    // xor_fetch
    x = 1;
    r = __atomic_xor_fetch(&x, 3, __ATOMIC_SEQ_CST);
    ASSERT(2, r);
    ASSERT(2, x);

    // fetch_nand
    x = 0x0F;
    r = __atomic_fetch_nand(&x, 0xF0, __ATOMIC_SEQ_CST);
    ASSERT(0x0F, r);
    ASSERT(~(0x0F & 0xF0), x);

    // nand_fetch
    x = 0x0F;
    r = __atomic_nand_fetch(&x, 0xF5, __ATOMIC_SEQ_CST);
    ASSERT(~(0x0F & 0xF5), r);
    ASSERT(~(0x0F & 0xF5), x);
}

void test_builtin_variants() {
    int x = 100;
    int r;

    r = __builtin_atomic_fetch_add(&x, 10, __ATOMIC_SEQ_CST);
    ASSERT(100, r);
    ASSERT(110, x);

    r = __builtin_atomic_fetch_sub(&x, 10, __ATOMIC_SEQ_CST);
    ASSERT(110, r);
    ASSERT(100, x);
}

void test_types() {
    char c = 10;
    __atomic_fetch_add(&c, 1, __ATOMIC_SEQ_CST);
    ASSERT(11, c);

    short s = 1000;
    __atomic_fetch_add(&s, 1, __ATOMIC_SEQ_CST);
    ASSERT(1001, s);

    long l = 1000000;
    __atomic_fetch_add(&l, 1, __ATOMIC_SEQ_CST);
    ASSERT(1000001, l);
}

void test_exchange() {
    int x = 10;
    int r = __atomic_exchange_n(&x, 20, __ATOMIC_SEQ_CST);
    ASSERT(10, r);
    ASSERT(20, x);

    int old_v = 20;
    bool success = __atomic_compare_exchange_n(&x, &old_v, 30, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    ASSERT(true, success);
    ASSERT(30, x);

    success = __atomic_compare_exchange_n(&x, &old_v, 40, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    ASSERT(false, success);
    ASSERT(30, old_v);
    ASSERT(30, x);
}

void test_load_store() {
    int x = 10;
    int r = __atomic_load_n(&x, __ATOMIC_SEQ_CST);
    ASSERT(10, r);

    __atomic_store_n(&x, 20, __ATOMIC_SEQ_CST);
    ASSERT(20, x);
}

int main(void) {
    test_int_variants();
    test_builtin_variants();
    test_types();
    test_exchange();
    test_load_store();

    printf("OK\n");
    return 0;
}
