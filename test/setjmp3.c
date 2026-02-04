// jmp_test.c
#include "test.h"
#include <setjmp.h>

jmp_buf jb;

int f(int x) {
    if (x == 0)
        longjmp(jb, 42);
    return f(x - 1) + 1;
}

int main(void) {
    int v = setjmp(jb);
    if (v == 0)
        f(100);
    printf("v=%d\n", v); // must print 42
    ASSERT(v, 42);
    return 0;
}
