
#include <string.h>
#include "test.h"

int main() {
    char src[] = "Hello, world!";
    char dest[20];
    memcpy(dest, src, strlen(src) + 1); // Use memcpy instead of __builtin_memcpy
    printf("Copied string: %s\n", dest);
    ASSERT(1, !strcmp(dest, "Hello, world!"));
    return 0;
}
