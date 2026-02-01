#include <stdio.h>
#include <stdlib.h>

struct S {
    int a;
    int b[10];
    void *p;
};

void target(int a, struct S s, int b, int c, int d, int e, int f, long *g, long *h) {
    if (s.a != 42) {
        printf("FAIL: s.a expected 42, got %d\n", s.a);
        exit(1);
    }
    if (g == NULL || h == NULL) {
        printf("FAIL: g or h is NULL\n");
        exit(1);
    }
    *g = 123;
    *h = 456;
    printf("target: s.a=%d, g=%p, h=%p\n", s.a, g, h);
}

int main() {
    struct S s = {0};
    s.a = 42;
    long g = 0, h = 0;
    // a=1, s=s, b=2, c=3, d=4, e=5, f=6, g=&g, h=&h
    target(1, s, 2, 3, 4, 5, 6, &g, &h);
    if (g == 123 && h == 456) {
        printf("SUCCESS\n");
        return 0;
    }
    printf("FAIL: g=%ld, h=%ld\n", g, h);
    return 1;
}
