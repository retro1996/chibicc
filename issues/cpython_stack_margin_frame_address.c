// Reproducer for CPython's stack margin check using __builtin_frame_address(0).
//
// This intentionally builds a stack-consuming call path and then applies the
// same 25% safety rule as test_call.TestRecursion.test_margin_is_sufficient:
//   safe_margin = raw_delta * 5 / 4
//   assert(safe_margin < 16384)
//
// Typical behavior on this machine:
// - gcc -O2 -fno-omit-frame-pointer -fno-optimize-sibling-calls: PASS
// - chibicc -fno-omit-frame-pointer: FAIL (safe_margin > 16384)
//
// Build/run:
//   gcc -O2 -fno-omit-frame-pointer -fno-optimize-sibling-calls \
//       issues/cpython_stack_margin_frame_address.c -o /tmp/margin_gcc && /tmp/margin_gcc
//   ./chibicc -std=c11 -fno-omit-frame-pointer \
//       -o /tmp/margin_chibicc issues/cpython_stack_margin_frame_address.c && /tmp/margin_chibicc

#include <stdint.h>
#include <stdio.h>

#define STACK_MARGIN 16384
#define DEPTH 100
#define PAD 96

static uintptr_t addrs[DEPTH];
static volatile int sink;

__attribute__((noinline))
static uintptr_t get_stack_pointer(void) {
  return (uintptr_t)__builtin_frame_address(0);
}

__attribute__((noinline))
static void recurse(int depth) {
  volatile char local[PAD];
  local[0] = (char)depth;
  addrs[depth] = get_stack_pointer();

  if (depth + 1 < DEPTH)
    recurse(depth + 1);

  // Keep this after the recursive call to block tail-call elimination.
  sink += local[0];
}

int main(void) {
  recurse(0);

  uintptr_t min = addrs[0];
  uintptr_t max = addrs[0];
  for (int i = 1; i < DEPTH; i++) {
    if (addrs[i] < min)
      min = addrs[i];
    if (addrs[i] > max)
      max = addrs[i];
  }

  uintptr_t raw_delta = max - min;
  uintptr_t safe_margin = (raw_delta * 5) / 4;

  printf("raw_delta    = %lu\n", (unsigned long)raw_delta);
  printf("safe_margin  = %lu\n", (unsigned long)safe_margin);
  printf("stack_margin = %d\n", STACK_MARGIN);

  if (safe_margin < STACK_MARGIN) {
    printf("PASS: safe_margin < stack_margin\n");
    return 0;
  }

  printf("REPRODUCED: safe_margin >= stack_margin\n");
  return 1;
}
