// tls_test.c
#include "test.h"

__thread int tls;

int main(void) {
    tls = 123;
    printf("%d\n", tls);
    ASSERT(tls, 123);
    return 0;
}
