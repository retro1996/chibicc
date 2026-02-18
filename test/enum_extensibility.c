
#include "test.h"
// enum_extensibility_basic.c

enum __attribute__((enum_extensibility(open))) Color {
    RED,
    GREEN,
    BLUE
};

enum __attribute__((enum_extensibility(closed))) Shape {
    CIRCLE,
    SQUARE
};

int main(void) {
    enum Color c = RED;
    enum Shape s = CIRCLE;
    printf("%d %d\n", c, s);
    ASSERT(RED, c);
    ASSERT(CIRCLE, s);
    printf("OK\n");
    return 0;
}
