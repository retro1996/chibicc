#include "test.h"
#include <stdbool.h>

_Bool str_lit_bool_init = "abc" ? "foo" && "bar" : 0;


int main() {
    ASSERT(1, str_lit_bool_init);
    return 0;
}