// test_stack_margin.c
// gcc -O2 -fno-omit-frame-pointer test_stack_margin.c -o test_stack_margin

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#define STACK_MARGIN 16384   // Mimics _testinternalcapi.get_stack_margin()
#define DEPTH        100

static uintptr_t stack_addrs[DEPTH];

__attribute__((noinline))
static void recurse(int depth) {
    volatile char local[256];  // simulate frame growth
    (void)local;

    uintptr_t sp;
    __asm__ volatile("mov %%rsp, %0" : "=r"(sp));

    stack_addrs[depth] = sp;

    if (depth + 1 < DEPTH)
        recurse(depth + 1);
}

int main(void) {
    recurse(0);

    uintptr_t min = stack_addrs[0];
    uintptr_t max = stack_addrs[0];

    for (int i = 1; i < DEPTH; i++) {
        if (stack_addrs[i] < min)
            min = stack_addrs[i];
        if (stack_addrs[i] > max)
            max = stack_addrs[i];
    }

    size_t used = max - min;
    size_t safe_margin = used + 1024;  // CPython-style safety buffer

    printf("stack used     = %zu bytes\n", used);
    printf("safe margin    = %zu bytes\n", safe_margin);
    printf("stack margin   = %d bytes\n", STACK_MARGIN);

    assert(safe_margin < STACK_MARGIN &&
           "safe_margin exceeds stack_margin (CPython invariant broken)");

    return 0;
}
