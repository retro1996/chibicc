// math_abi_torture.c
#include "test.h"
#include <math.h>
#include <fenv.h>
#include <errno.h>

#pragma STDC FENV_ACCESS ON

static double chain(double x) {
    return sin(cos(tan(log(exp(x)))));
}


long double f(long double x) {
    return sqrtl(x) + sinl(x);
}


int main(void) {
    feclearexcept(FE_ALL_EXCEPT);
    errno = 0;

    volatile double x = 0.1;
    volatile double y = 0.0;

    for (int i = 0; i < 100000; i++) {
        y += chain(x + i * 1e-6);
    }

    int raised = fetestexcept(FE_ALL_EXCEPT);

    printf("y=%f errno=%d fpex=%x\n", y, errno, raised);
    ASSERT(83500, y);
    ASSERT(0, errno);
    ASSERT(32, raised);
    volatile long double x1 = 1.234567890123456789L;
    volatile long double y1 = f(x1);
    printf("%.18Lf\n", y1);
    ASSERT(2.718281828459045091L, y1);
    return 0;
}
