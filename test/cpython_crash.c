#include "test.h"
#include <alloca.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * This test attempts to reproduce a crash seen during CPython compilation (_freeze_module).
 * It exercises recursion, alloca, and stack arguments.
 */

int recursive_fn(int depth, int a, int b, int c, int d, int e, int f, int g, int h) {
    if (depth <= 0) {
        return a + b + c + d + e + f + g + h;
    }

    // Allocate variable size on stack to shift things around
    // Size is at least 16 to ensure we test non-trivial alloca
    int size = (depth % 16) * 8 + 16;
    char *ptr = alloca(size);
    
    // Fill memory to check for corruption later
    memset(ptr, depth & 0xFF, size);

    // Recursive call with modified arguments
    // Arguments g and h are typically passed on stack (x86-64 System V ABI uses 6 registers)
    int res = recursive_fn(depth - 1, a+1, b+1, c+1, d+1, e+1, f+1, g+1, h+1);

    // Verify memory integrity
    for (int i = 0; i < size; i++) {
        if ((unsigned char)ptr[i] != (depth & 0xFF)) {
            printf("Stack corruption detected at depth %d, index %d\n", depth, i);
            exit(1);
        }
    }

    return res;
}

int main() {
    // 100 levels of recursion
    // Initial args: 1, 2, 3, 4, 5, 6, 7, 8
    // Sum: 36
    // At depth 0 (after 100 steps): args are 101, 102, ..., 108
    // Sum: 36 + 8*100 = 836
    
    int res = recursive_fn(100, 1, 2, 3, 4, 5, 6, 7, 8);
    printf("Result: %d\n", res);
    ASSERT(836, res);

    printf("OK\n");
    return 0;
}
