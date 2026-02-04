#include "test.h"
#include <math.h>

int main(void) {
    double x = 1.25;
    double y = -1.25;

    printf("isnormal(1.25) = %d\n", isnormal(x));
    printf("issubnormal(1.25) = %d\n",
           fpclassify(x) == FP_SUBNORMAL);
    printf("signbit(-1.25) = %d\n", signbit(y));
    printf("isnormal(1.25) = %d\n", isnormal(1.25));
    printf("issubnormal(1.25) = %d\n",
           fpclassify(1.25) == FP_SUBNORMAL);
    ASSERT(1, isnormal(x));
    ASSERT(0, fpclassify(x) == FP_SUBNORMAL);
    ASSERT(1, signbit(y));
    ASSERT(1, isnormal(1.25));
    ASSERT(0, fpclassify(1.25) == FP_SUBNORMAL);
    return 0;
}
