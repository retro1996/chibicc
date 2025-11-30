#include <stdio.h>
#include <xmmintrin.h>   
#include <pmmintrin.h>   
#include <stdint.h>
#include "test.h"

int main() {
    // Initialize two vectors
    __m128 a = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f); // [4,3,2,1]
    __m128 b = _mm_set_ps(10.0f, 20.0f, 30.0f, 40.0f); // [40,30,20,10]

    // Call the intrinsic
    __m128 result = __builtin_ia32_addsubps(a, b);

    // Extract and print each float
    float *f = (float*)&result;
    printf("Result: %f %f %f %f\n", f[0], f[1], f[2], f[3]);

    // Expected behavior: alternates add/sub
    // result[0] = a[0] + b[0] = 4 + 40 = 44
    // result[1] = a[1] - b[1] = 3 - 30 = -27
    // result[2] = a[2] + b[2] = 2 + 20 = 22
    // result[3] = a[3] - b[3] = 1 - 10 = -9
    __m128 hsub_result = __builtin_ia32_hsubps(a, b);
    float *hsub_f = (float*)&hsub_result;
    printf("HSUB result: %f %f %f %f\n", hsub_f[0], hsub_f[1], hsub_f[2], hsub_f[3]);

        // Horizontal add
    __m128 hadd_result = __builtin_ia32_haddps(a, b);
    float *hadd_f = (float*)&hadd_result;
    printf("HADD result: %f %f %f %f\n", hadd_f[0], hadd_f[1], hadd_f[2], hadd_f[3]);

    printf("OK\n");
    ASSERT(-36, result[0]);
    ASSERT(33, result[1]);
    ASSERT(-18, result[2]);
    ASSERT(11, result[3]);
    ASSERT(1, hsub_f[0]);
    ASSERT(1, hsub_f[1]);
    ASSERT(10, hsub_f[2]);
    ASSERT(10, hsub_f[3]);
    ASSERT(7, hadd_f[0]);
    ASSERT(3, hadd_f[1]);
    ASSERT(70, hadd_f[2]);
    ASSERT(30, hadd_f[3]);

    return 0;
}
