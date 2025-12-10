#include "test.h"

int main() {
    int x = 0, y;

    __atomic_load_n(&x, 0);
    ASSERT(0, x);
    __atomic_store_n(&x, 0, 0);
    ASSERT(0, x);
    __atomic_exchange_n(&x, 1, 0);
    ASSERT(1, x);
    __atomic_compare_exchange_n(&x, &y, 1, 0, 0, 0);
    ASSERT(1, x);
    __atomic_fetch_add(&x, 1, 0);
    ASSERT(2, x);
    __atomic_fetch_sub(&x, 1, 0);
    ASSERT(1, x);
    __atomic_fetch_or(&x, 1, 0);
    ASSERT(1, x);
    __atomic_fetch_and(&x, 1, 0);
    ASSERT(1, x);
    __atomic_fetch_xor(&x, 1, 0);
    ASSERT(0, x);
    __sync_add_and_fetch(&x, 1);
    ASSERT(1, x);
    printf("atomic5 OK\n");
    return 0;
}
