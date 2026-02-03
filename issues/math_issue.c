#include "test.h"
#include <math.h>

int main(void) {
    double x = 1.25;
    double y = -1.25;

    printf("isnormal(1.25) = %d\n", isnormal(x));
    printf("issubnormal(1.25) = %d\n",
           fpclassify(x) == FP_SUBNORMAL);
    printf("signbit(-1.25) = %d\n", signbit(y));
    return 0;
}
