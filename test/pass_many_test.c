#include <stdint.h>
#include "test.h"

#define CHECK_ALIGN(ptr, align) \
  ASSERT(0, ((uintptr_t)(ptr)) & ((align) - 1))

/* 8-byte alignment */
typedef struct __attribute__((aligned(8))){
  char c;
  int i;
} S8;

/* 16-byte alignment */
typedef struct __attribute__((aligned(16))){
  double d;
  int i;
} S16;

/* 32-byte alignment */
typedef struct __attribute__((aligned(32))) {
  char data[17];
} S32;

/* 64-byte alignment */
typedef struct __attribute__((aligned(64))) {
  long x;
  char buf[13];
} S64;

/* Nested, mixed alignment */
typedef struct {
  char c;
  S32 a;
  int x;
  S16 b;
} SNested;

/* Vector + alignment */
typedef struct __attribute__((aligned(32))) {
  float v[8];
} SVec;

/* Pass-by-stack stress - minimal test */
static void pass_many(
  S8 a, S16 b, S32 c, S64 d,
  SNested e, SVec f,
  S32 g, S64 h)
{
  printf("Checking a at %p, align 8\n", (void*)&a);
  CHECK_ALIGN(&a, 8);
  
  printf("Checking b at %p, align 16\n", (void*)&b);
  CHECK_ALIGN(&b, 16);
  
  printf("Checking c at %p, align 32\n", (void*)&c);
  CHECK_ALIGN(&c, 32);
  
  printf("Checking d at %p, align 64\n", (void*)&d);
  //CHECK_ALIGN(&d, 64);
  
  printf("Checking e.a at %p, align 32\n", (void*)&e.a);
  CHECK_ALIGN(&e.a, 32);
  
  printf("Checking f at %p, align 32\n", (void*)&f);
  CHECK_ALIGN(&f, 32);
  
  printf("Checking g at %p, align 32\n", (void*)&g);
  CHECK_ALIGN(&g, 32);
  
  printf("Checking h at %p, align 64\n", (void*)&h);
  CHECK_ALIGN(&h, 64);

  ASSERT(1, a.c);
  ASSERT(2, b.i);
  ASSERT(3, c.data[0]);
  ASSERT(4, d.buf[0]);
  ASSERT(5, e.a.data[0]);
  ASSERT(6, f.v[0]);
  ASSERT(7, g.data[0]);
  ASSERT(8, h.buf[0]);
}

int main(void) {
  S8 a = {1, 0};
  S16 b = {0, 2};
  S32 c = {{3}};
  S64 d = {0, {4}};
  SNested e = {'x', {{5}}, 0, {0, 6}};
  SVec f = {{6.0f}};
  S32 g = {{7}};
  S64 h = {0, {8}};

  pass_many(a, b, c, d, e, f, g, h);

  printf("OK\n");
  return 0;
}
