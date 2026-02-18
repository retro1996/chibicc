#include <stdint.h>
#include <stdio.h>

/*
 * Reproducer for manual frame-pointer unwinding under -O3.
 *
 * Run with:
 *   ./chibicc -O3 -o issues/frame_pointer_unwind_o3.exe issues/frame_pointer_unwind_o3.c
 *   ./issues/frame_pointer_unwind_o3.exe
 *
 * Expected (with frame pointers omitted in recur_no_fp): short unwind chain.
 * Current chibicc behavior: deep chain (~recursion depth), indicating that
 * unwinding does not stop where frame pointers should be missing.
 */

typedef struct Frame {
  struct Frame *next;
  void *ret;
} Frame;

typedef struct Stats {
  int length;
} Stats;

__attribute__((noinline)) static void manual_unwind(Stats *s) {
  Frame *fp = (Frame *)__builtin_frame_address(0);
  int n = 0;

  while (fp && n < 256) {
    Frame *next = fp->next;
    n++;

    if (!next)
      break;
    if ((uintptr_t)next <= (uintptr_t)fp)
      break;
    if ((uintptr_t)next - (uintptr_t)fp > (1u << 20))
      break;

    fp = next;
  }

  s->length = n;
}

__attribute__((noinline)) static void leaf_unwind(Stats *s) {
  volatile void *fp = __builtin_frame_address(0);
  (void)fp;
  manual_unwind(s);
}

__attribute__((noinline)) static void recur_no_fp(int n, Stats *s) {
  volatile int keep = n;

  if (n == 0) {
    leaf_unwind(s);
  } else {
    recur_no_fp(n - 1, s);
  }

  if (keep == 123456789)
    printf("%d\n", n);
}

__attribute__((noinline)) static void outer_with_fp(int n, Stats *s) {
  volatile void *fp = __builtin_frame_address(0);
  (void)fp;
  recur_no_fp(n, s);
}

int main(void) {
  enum { DEPTH = 100, MAX_EXPECTED = 16 };
  Stats s = {0};

  outer_with_fp(DEPTH, &s);

  printf("{\"length\": %d, \"recur_depth\": %d}\n", s.length, DEPTH);

  if (s.length > MAX_EXPECTED) {
    printf("BUG: manual unwind ignored omitted frame pointers (length=%d)\n",
           s.length);
    return 1;
  }

  return 0;
}
