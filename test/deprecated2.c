#include "test.h"

#define Py_DEPRECATED(version) __attribute__((deprecated))

typedef long Py_hash_t;

struct S {
    Py_DEPRECATED(3.11) Py_hash_t ob_shash;
};

int main(void) {
    struct S s;
    (void)s;
    s.ob_shash = 8;
    printf("%ld\n", s.ob_shash);
    ASSERT(8, s.ob_shash);
    return 0;
}

