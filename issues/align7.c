#include "test.h"
#include <stdint.h>
_Alignas(32) int x;


long double f(long double x) {
    return x + 1.0L;
}



long double f2(long double *p) {
    return p[1];
}

typedef __attribute__((aligned(32))) int A;


int main() {
    char __attribute__((aligned(32))) buf[3];
    long double x = 3.0L;
    printf("%Lf\n", f(x));
    printf("%p\n", (void *)buf);
    ASSERT(0, ((uintptr_t)buf % 32) != 0);      
    int __attribute__((aligned(32))) y;   
    ASSERT(1, (int)f(y));

    A z;
    ASSERT(0, (((uintptr_t)&z % 32) != 0));

    return 0;
    
}
