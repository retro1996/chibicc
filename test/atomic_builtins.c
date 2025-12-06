#include "test.h"

int main(void) {
    int x = 10;
    int y = 20;
    int z = 30;

    printf("=== __atomic_fetch_* tests ===\n");

    int a1 = __atomic_fetch_add(&x, 5, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_add: old=%d new=%d\n", a1, x);
    ASSERT(15, x);
    ASSERT(10, a1);
    int a2 = __atomic_fetch_sub(&x, 3, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_sub: old=%d new=%d\n", a2, x);
    ASSERT(12, x);
    ASSERT(15, a2);
    int a3 = __atomic_fetch_or(&x, 0x10, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_or:  old=%d new=%d\n", a3, x);
    ASSERT(28, x);
    ASSERT(12, a3);
    int a4 = __atomic_fetch_and(&x, 0x0F, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_and: old=%d new=%d\n", a4, x);
    ASSERT(12, x);
    ASSERT(28, a4);
    int a5 = __atomic_fetch_xor(&x, 0xFF, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_xor: old=%d new=%d\n", a5, x);
    ASSERT(243, x);
    ASSERT(12, a5);
    int a6 = __atomic_fetch_nand(&x, 0xF0, __ATOMIC_SEQ_CST);
    printf("__atomic_fetch_nand: old=%d new=%d\n", a6, x);
    ASSERT(-241, x);
    ASSERT(243, a6);

    printf("\n=== __sync_* tests ===\n");

    int s1 = __sync_fetch_and_add(&y, 5);
    printf("__sync_fetch_and_add: old=%d new=%d\n", s1, y);
    ASSERT(25, y);
    ASSERT(20, s1);
    int s2 = __sync_add_and_fetch(&y, 5);
    printf("__sync_add_and_fetch: new=%d\n", s2);
    ASSERT(30, y);
    ASSERT(30, s2);
    int s3 = __sync_fetch_and_sub(&y, 2);
    printf("__sync_fetch_and_sub: old=%d new=%d\n", s3, y);
    ASSERT(28, y);
    ASSERT(30, s3);
    int s4 = __sync_sub_and_fetch(&y, 3);
    printf("__sync_sub_and_fetch: new=%d\n", s4);
    ASSERT(25, y);
    ASSERT(25, s4);
    int s5 = __sync_fetch_and_or(&y, 0x10);
    printf("__sync_fetch_and_or: old=%d new=%d\n", s5, y);
    ASSERT(25, y);
    ASSERT(25, s5);
    int s6 = __sync_fetch_and_and(&y, 0x0F);
    printf("__sync_fetch_and_and: old=%d new=%d\n", s6, y);
    ASSERT(9, y);
    ASSERT(25, s6);
    int s7 = __sync_fetch_and_xor(&y, 0xFF);
    printf("__sync_fetch_and_xor: old=%d new=%d\n", s7, y);
    ASSERT(246, y);
    ASSERT(9, s7);
    int s8 = __sync_fetch_and_nand(&y, 0xF0);
    printf("__sync_fetch_and_nand: old=%d new=%d\n", s8, y);
    ASSERT(-241, y);
    ASSERT(246, s8);
    int c1 = __sync_bool_compare_and_swap(&z, 30, 99);
    printf("__sync_bool_compare_and_swap: result=%d new=%d\n", c1, z);
    ASSERT(99, z);
    ASSERT(1, c1);
    int c2 = __sync_val_compare_and_swap(&z, 99, 123);
    printf("__sync_val_compare_and_swap: old=%d new=%d\n", c2, z);
    ASSERT(123, z);
    ASSERT(99, c2);

    __sync_lock_test_and_set(&z, 777);
    printf("__sync_lock_test_and_set: new=%d\n", z);
    ASSERT(777, z);
    __sync_lock_release(&z);
    printf("__sync_lock_release: new=%d\n", z);
    ASSERT(0, z);
    return 0;
}
