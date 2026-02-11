// Reproducer for CPython's test_frame_pointer_unwind failure mode.
//
// Compile with:
//   ./chibicc -O3 -fomit-frame-pointer -o issues/test_frame_pointer_unwind.exe \
//     issues/test_frame_pointer_unwind.c
//
// On the buggy behavior, a frame-pointer requirement in one function leaks to
// unrelated functions, and manual unwind sees a deep frame chain.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// This function must keep frame pointer.
__attribute__((noinline))
static void force_fp_here_only(void) {
  (void)__builtin_frame_address(0);
}

__attribute__((noinline))
static int manual_unwind_count(void) {
  uintptr_t *start = (uintptr_t *)__builtin_frame_address(0);
  uintptr_t *fp = (uintptr_t *)*start;
  int count = 0;

  while (fp && count < 256) {
    uintptr_t cur = (uintptr_t)fp;
    uintptr_t low = (uintptr_t)start;

    // Stop on invalid/non-monotonic frame links.
    if (cur <= low)
      break;
    if ((cur - low) > (1UL << 20))
      break;
    if (cur & 7)
      break;

    count++;
    start = fp;
    fp = (uintptr_t *)*fp;
  }

  return count;
}

static int (*volatile next_call)(int);

__attribute__((noinline))
static int build_stack(int n) {
  volatile int keep = n;
  if (n == 0)
    return manual_unwind_count();

  // Deliberately non-tail recursion via volatile function pointer.
  int r = next_call(n - 1);
  return r + (keep - keep);
}

int main(void) {
  force_fp_here_only();
  next_call = build_stack;

  int depth = build_stack(100);
  printf("manual_unwind depth=%d\n", depth);

  // With -fomit-frame-pointer on x86_64, unrelated functions should not keep
  // frame pointers; expected unwind depth is tiny (0-2 depending on runtime).
  if (depth > 2) {
    printf("FAIL: unexpected deep frame chain\n");
    return 1;
  }

  printf("OK\n");
  return 0;
}
