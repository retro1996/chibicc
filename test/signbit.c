// test-signbit.c
#include <math.h>
#include <stdlib.h>
#include "test.h"
// #define signbitf(x) __builtin_signbit(x)
// #define signbitl(x)  __builtin_signbit(x)
  
int main(void) {
  /* ---------- float ---------- */
  {
    volatile float pz = 0.0f;
    volatile float nz = -0.0f;
    volatile float pn = 1.0f;
    volatile float nn = -1.0f;
    volatile float pinf = 1.0f / 0.0f;
    volatile float ninf = -1.0f / 0.0f;
    volatile float pnan = 0.0f / 0.0f;
    volatile float nnan = -(0.0f / 0.0f);

    ASSERT(0, !!signbitf(pz));
    ASSERT(1, !!signbitf(nz));
    ASSERT(0, !!signbitf(pn));
    ASSERT(1, !!signbitf(nn));
    ASSERT(0, !!signbitf(pinf));
    ASSERT(1, !!signbitf(ninf));
    ASSERT(1, !!signbitf(pnan));
    ASSERT(0, !!signbitf(nnan));
  }

  /* ---------- double ---------- */
  {
    volatile double pz = 0.0;
    volatile double nz = -0.0;
    volatile double pn = 1.0;
    volatile double nn = -1.0;
    volatile double pinf = 1.0 / 0.0;
    volatile double ninf = -1.0 / 0.0;
    volatile double pnan = 0.0 / 0.0;
    volatile double nnan = -(0.0 / 0.0);

    ASSERT(0, !!signbit(pz));
    ASSERT(1, !!signbit(nz));
    ASSERT(0, !!signbit(pn));
    ASSERT(1, !!signbit(nn));
    ASSERT(0, !!signbit(pinf));
    ASSERT(1, !!signbit(ninf));
    ASSERT(1, !!signbit(pnan));
    ASSERT(0, !!signbit(nnan));
  }

  /* ---------- long double ---------- */
  {
    volatile long double pz = 0.0L;
    volatile long double nz = -0.0L;
    volatile long double pn = 1.0L;
    volatile long double nn = -1.0L;
    volatile long double pinf = 1.0L / 0.0L;
    volatile long double ninf = -1.0L / 0.0L;
    volatile long double pnan = 0.0L / 0.0L;
    volatile long double nnan = -(0.0L / 0.0L);

    ASSERT(0, !!signbitl(pz));
    ASSERT(1, !!signbitl(nz));
    ASSERT(0, !!signbitl(pn));
    ASSERT(1, !!signbitl(nn));
    ASSERT(0, !!signbitl(pinf));
    ASSERT(1, !!signbitl(ninf));
    ASSERT(1, !!signbitl(pnan));
    ASSERT(0, !!signbitl(nnan));
  }

  /* ---------- builtin directly ---------- */
  {
    volatile long double x = -0.0L;
    ASSERT(1, !!__builtin_signbit(x));
  }

  return 0;
}