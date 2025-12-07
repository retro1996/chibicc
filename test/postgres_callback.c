#include "test.h"
#include <stdint.h>
#include <stddef.h>

typedef uint64_t Datum;
typedef void (*pg_on_exit_callback)(int code, Datum arg);

struct ONEXIT {
    pg_on_exit_callback function;
    Datum arg;
};

// Simulate Int32GetDatum macro from PostgreSQL
static inline Datum Int32GetDatum(int32_t i) {
    return (Datum)(uint32_t)i;  // cast to 32-bit first, then 64-bit Datum
}

// Dummy callback function
void dummy_callback(int code, Datum arg) {
    printf("dummy_callback called with code=%d, arg=0x%lx\n", code, arg);
}

int main() {
    struct ONEXIT onexit;

    onexit.function = dummy_callback;
    onexit.arg = Int32GetDatum(123456789);

    printf("sizeof(ONEXIT) = %zu\n", sizeof(struct ONEXIT));
    printf("offset function = %zu\n", offsetof(struct ONEXIT, function));
    printf("offset arg      = %zu\n", offsetof(struct ONEXIT, arg));
    ASSERT(16, sizeof(struct ONEXIT));
    ASSERT(0, offsetof(struct ONEXIT, function));
    ASSERT(8, offsetof(struct ONEXIT, arg));

    // Call the callback to see the stored value
    onexit.function(0, onexit.arg);

    return 0;
}
