
#include "test.h"


int main() {
    int value = 5;
    int result = __sync_bool_compare_and_swap(&value, 5, 10);
    printf("Compare and swap result: %d, New value: %d\n", result, value); // Result: 1, value: 5
    ASSERT(1, result);
    ASSERT(10, value);
    return 0;
}

