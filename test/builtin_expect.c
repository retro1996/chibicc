
#include "test.h"
int main() {
    int x = 10;
    int lhs = 0;
    int rhs = 0;

    if (__builtin_expect(x == 10, 1)) {
        printf("Expected branch\n");
    } else {
        printf("Unexpected branch\n");
        ASSERT(0, 1); // This should not happen
    }

    if (__builtin_expect(x == 5, 1)) {
        printf("Expected branch 2\n");
        ASSERT(0, 1); // This should not happen
    } else {
        printf("Unexpected branch 2\n");
    }

    int ret = __builtin_expect((lhs = 7), (rhs = 9));
    ASSERT(7, ret);
    ASSERT(7, lhs);
    ASSERT(9, rhs);
    return 0;
}

