#include <stdint.h>
#include <stdio.h>

// Reproducer for CPython -O3 regressions seen in:
// - test_call.TestRecursion.test_margin_is_sufficient
// - test_frame_pointer_unwind / faulthandler frame walking behavior
//
// Usage:
//   gcc -O3 -std=c11 issues/test_cpython_o3_repro.c -o /tmp/repro_gcc && /tmp/repro_gcc
//   ./chibicc -O3 -std=c11 issues/test_cpython_o3_repro.c -o /tmp/repro_chi && /tmp/repro_chi
//
// Expected today:
//   gcc:     NOT_REPRODUCED (exit 0)
//   chibicc: REPRODUCED     (exit 1)

#define CPYTHON_STACK_MARGIN 16384

__attribute__((noinline)) static uintptr_t get_stack_pointer(void) {
  return (uintptr_t)__builtin_frame_address(0);
}

__attribute__((noinline)) static uintptr_t vectorcall_like(uintptr_t (*fn)(void)) {
  // GCC -O3 folds these temporaries away; chibicc currently keeps them on stack.
  char tmp1[8192];
  char tmp2[8192];
  for (int i = 0; i < 8192; i++) {
    tmp1[i] = (char)i;
    tmp2[i] = (char)(i + 1);
  }
  int guard = tmp1[0] + tmp2[8191];
  if (guard == 123456)
    puts("impossible");
  return fn();
}

__attribute__((noinline)) static void *toggle_frame_pointer_mode(void) {
  // In chibicc parse.c this currently disables omit-frame-pointer globally
  // for the rest of the translation unit.
  return __builtin_frame_address(0);
}

__attribute__((noinline)) static int manual_unwind_len(void) {
  uintptr_t *fp = (uintptr_t *)__builtin_frame_address(0);
  int len = 0;

  for (int i = 0; i < 200 && fp; i++) {
    uintptr_t fp_addr = (uintptr_t)fp;
    uintptr_t *next_fp = (uintptr_t *)fp[0];

    len++;

    if ((uintptr_t)next_fp < 4096)
      break;
    if ((uintptr_t)next_fp <= fp_addr)
      break;

    fp = next_fp;
  }

  return len;
}

__attribute__((noinline)) static int build_stack(int n) {
  volatile int keep = n;
  if (n == 0)
    return manual_unwind_len() + keep;

  int r = build_stack(n - 1);
  return r + (keep & 0);
}

int main(void) {
  uintptr_t sp0 = get_stack_pointer();
  uintptr_t sp1 = vectorcall_like(get_stack_pointer);
  uintptr_t delta = (sp0 > sp1) ? (sp0 - sp1) : (sp1 - sp0);
  double safe_margin = delta * 5.0 / 4.0;

  void *p = toggle_frame_pointer_mode();
  if (p == (void *)1)
    puts("unreachable");
  int unwind = build_stack(40);

  printf("safe_margin=%.1f (limit=%d)\n", safe_margin, CPYTHON_STACK_MARGIN);
  printf("manual_unwind_len=%d\n", unwind);

  int reproduced = 0;
  if (safe_margin >= CPYTHON_STACK_MARGIN)
    reproduced = 1;
  if (unwind > 10)
    reproduced = 1;

  if (reproduced) {
    printf("REPRODUCED\n");
    return 1;
  }

  printf("NOT_REPRODUCED\n");
  return 0;
}
