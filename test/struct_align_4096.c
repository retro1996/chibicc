#include "test.h"
#include <stdint.h>

typedef struct __attribute__((aligned(4096))) S4096 {
    char data[127];
} S4096;

#define CHECK_ALIGN(ptr, n) \
  ASSERT(0, ((uintptr_t)(ptr)) & ((n) - 1))

static void local_struct(int n) {
    if (n == 0)
        return;

    S4096 s;
    CHECK_ALIGN(&s, 4096);
    CHECK_ALIGN(&s.data[0], 4096);

    local_struct(n - 1);
}

static void pass_by_value(int n, S4096 s) {
    if (n == 0)
        return;

    CHECK_ALIGN(&s, 4096);
    CHECK_ALIGN(&s.data[0], 4096);

    pass_by_value(n - 1, s);
}

static void mixed(int n, S4096 s) {
    if (n == 0)
        return;

    CHECK_ALIGN(&s, 4096);

    int x = 1;
    (void)x;

    S4096 local;
    CHECK_ALIGN(&local, 4096);

    mixed(n - 1, local);
}

int main(void) {
    S4096 s;
    CHECK_ALIGN(&s, 4096);

    local_struct(4);
    pass_by_value(4, s);
    mixed(4, s);

    printf("OK\n");
    return 0;
}
