#include "test.h"
#include <stdarg.h>
struct S {
    long i, j;
};
void fn(int cnt, ... ) {
    va_list ap;
    va_start(ap, cnt);
    for (int i = 0; i < cnt; i++) {
        struct S s = va_arg(ap, struct S);
        printf("%ld,%ld,", s.i, s.j); // expected 1,2,3,4,5,6
        ASSERT(i*2+1, s.i);
        ASSERT(i*2+2, s.j);
    }
    printf("\n");
    va_end(ap);
}
int main(void) {
    struct S s0 = {1,2};
    struct S s1 = {3,4};
    struct S s2 = {5,6};

    fn(3, s0, s1, s2);
    return 0;
}