
#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

void add_vecs(float4 *a, float4 *b, float4 *result) {
    for (int i = 0; i < 4; i++) {
        (*result)[i] = (*a)[i] + (*b)[i];
    }
}

int main() {
    float4 a = {1.0, 2.0, 3.0, 4.0};
    float4 b = {10.0, 20.0, 30.0, 40.0};
    float4 result = {0};

    add_vecs(&a, &b, &result);

    printf("result[0]=%f\n", result[0]);
    printf("result[1]=%f\n", result[1]);
    printf("result[2]=%f\n", result[2]);
    printf("result[3]=%f\n", result[3]);
    ASSERT(11, result[0]);
    ASSERT(22, result[1]);
    ASSERT(33, result[2]);
    ASSERT(44, result[3]);

    return 0;
}
