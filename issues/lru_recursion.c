// Reproducer for CPython-like LRU recursion stack-overflow failures.
//
// Build:
//   ./chibicc -O3 -fomit-frame-pointer -o issues/lru_recursion.exe issues/lru_recursion.c
//   gcc -O3 -fomit-frame-pointer -o issues/lru_recursion_gcc.exe issues/lru_recursion.c
//
// Run:
//   ./issues/lru_recursion.exe [depth]
//
// Default depth is 100000. The program emulates a recursive LRU-style wrapper
// chain and aborts with a CPython-like fatal message if stack usage gets too
// close to an 8 MiB limit with a 16 KiB safety margin.

#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  STACK_LIMIT = 8 * 1024 * 1024,
  STACK_MARGIN = 16 * 1024,
  DEFAULT_DEPTH = 100000,
};

static uintptr_t stack_base;
static uintptr_t max_used;
static int stack_overflow;
static jmp_buf bailout;

static int *memo;
static unsigned char *seen;

static uintptr_t get_sp(void) {
  return (uintptr_t)__builtin_frame_address(0);
}

static void check_stack(void) {
  uintptr_t sp = get_sp();
  uintptr_t used = (stack_base >= sp) ? (stack_base - sp) : (sp - stack_base);
  if (used > max_used)
    max_used = used;

  if (used + STACK_MARGIN >= STACK_LIMIT) {
    stack_overflow = 1;
    longjmp(bailout, 1);
  }
}

static int fib_lru(int n);

// Prevent TCO and mimic an extra wrapper frame like functools._lru_cache_wrapper.
__attribute__((noinline))
static int lru_call(int n) {
  volatile int keep = n;
  int v = fib_lru(keep);
  return v + (keep - keep);
}

__attribute__((noinline))
static int fib_lru_impl(int n) {
  check_stack();

  if (n < 2)
    return n;

  if (seen[n])
    return memo[n];

  int a = lru_call(n - 1);
  int b = lru_call(n - 2);
  int v = a + b;
  seen[n] = 1;
  memo[n] = v;
  return v;
}

__attribute__((noinline))
static int fib_lru(int n) {
  check_stack();
  return fib_lru_impl(n);
}

int main(int argc, char **argv) {
  int depth = DEFAULT_DEPTH;
  if (argc > 1)
    depth = atoi(argv[1]);

  if (depth < 0) {
    fprintf(stderr, "depth must be >= 0\n");
    return 2;
  }

  memo = calloc((size_t)depth + 1, sizeof(int));
  seen = calloc((size_t)depth + 1, 1);
  if (!memo || !seen) {
    fprintf(stderr, "allocation failed\n");
    return 2;
  }

  stack_base = get_sp();
  max_used = 0;
  stack_overflow = 0;

  if (setjmp(bailout) == 0) {
    int r = fib_lru(depth);
    printf("depth=%d result=%d max_stack=%lu bytes\n", depth, r, (unsigned long)max_used);
    printf("OK\n");
  } else {
    printf("Fatal Python error: _Py_CheckRecursiveCall: Unrecoverable stack overflow (used %lu kB)\n",
           (unsigned long)(max_used / 1024));
    printf("Current thread [python] (most recent call first):\n");
    printf("  File \"test_functools.py\", line 2151 in fib\n");
  }

  free(memo);
  free(seen);
  return stack_overflow ? 1 : 0;
}
