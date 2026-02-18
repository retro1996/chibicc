#include <stdio.h>

#define REASSOC_FENCE(x, y) __asm__("" : "+r"(x), "+r"(y))

int main() {
    int a = 5;
    int b = 10;

    printf("Before fence: a=%d, b=%d\n", a, b);

    // Use the macro to prevent reassociation (GCC only)
    REASSOC_FENCE(a, b);

    // Perform a calculation
    int c = a + b;
    printf("After fence: c=%d\n", c);

    return 0;
}
