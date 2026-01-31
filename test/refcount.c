// macro_refcount_test.c
#include "test.h"
#include <stdlib.h>

struct O {
    long ref;
};

void dealloc(struct O *o) {
    printf("dealloc\n");
    free(o);
}

#define DECREF(o) do { \
    if (--((o)->ref) == 0) \
        dealloc(o); \
} while (0)

int main(void) {
    struct O *o = malloc(sizeof(*o));
    o->ref = 2;

    DECREF(o);
    DECREF(o);  // must dealloc exactly once

    return 0;
}
