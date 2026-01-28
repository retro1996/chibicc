/* test_infinity.c */
#include "test.h"
#include <math.h>

/* mimic CPython's Py_complex */
typedef struct {
    double real;
    double imag;
} Py_complex;

/* this triggers constant-expression evaluation */
Py_complex infj = {0.0, INFINITY};

int main(void) {
    printf("infj.imag = %f\n", infj.imag);
    printf("isinf(infj.imag) = %d\n", isinf(infj.imag));
    ASSERT(1, isinf(infj.imag));
    return 0;
}

