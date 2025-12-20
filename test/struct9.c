#include <stdarg.h>
#include "test.h"

typedef struct {
  float f;
} S1;

double test_s1(int tag, ...) {
  va_list ap;
  va_start(ap, tag);

  S1 s = va_arg(ap, S1);
  va_end(ap);

  return s.f;
}


typedef struct {
  int   i;
  float f;
} S3;

double test_s3(int tag, ...) {
  va_list ap;
  va_start(ap, tag);

  S3 s = va_arg(ap, S3);
  va_end(ap);

  return s.f;
}


typedef struct {
  char c;
} S4;

int test_s4(int tag, ...) {
  va_list ap;
  va_start(ap, tag);

  S4 s = va_arg(ap, S4);
  va_end(ap);

  return s.c;
}



int main(void) {
  S1 s = { 3.25f };

  double r = test_s1(0, s);
  printf("r = %.2f\n", r);
  ASSERT(3.25, r);

  S3 s = { 1, 2.75f };

  double r = test_s3(0, s);
  printf("r = %.2f\n", r);
  ASSERT(2.75, r);

  S4 s = { 7 };

  int r = test_s4(0, s);
  printf("r = %d\n", r);
  ASSERT(7, r);
  return 0;
}
