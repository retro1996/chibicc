#include "test.h"
int main(void) {
    struct Sub {
      int i;
    };
    struct S {
      struct Sub b;
      int j;
    };
    struct Sub b = {3};
    int junk = 2;
    struct S s[] = {b, 6, 7};

    printf("%d ", s[0].b.i);
    printf("%d ", s[0].j);
    printf("%d ", s[1].b.i);
    printf("%d\n", s[1].j); // expected {3 6 7 0}, got {3 *junk* 6 7}
    ASSERT(3, s[0].b.i);
    ASSERT(6, s[0].j);
    ASSERT(7, s[1].b.i);
    ASSERT(0, s[1].j);
    return 0;
}