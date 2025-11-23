#include <stdio.h>
int main() {
    if (__builtin_types_compatible_p(int, int)) {
        printf("Types are compatible\n");
    } else {
        printf("Types are not compatible\n");
    }
    if (__builtin_types_compatible_p(int, char)) {
        printf("Types are compatible\n");
    } else {
        printf("Types are not compatible\n");
    }
    if (__builtin_types_compatible_p(float, char)) {
        printf("Types are compatible\n");
    } else {
        printf("Types are not compatible\n");
    }
    if (__builtin_types_compatible_p(int, float)) {
        printf("Types are compatible\n");
    } else {
        printf("Types are not compatible\n");
    }
    if (__builtin_types_compatible_p(double, float)) {
        printf("Types are compatible\n");
    } else {
        printf("Types are not compatible\n");
    }    
    return 0;
}

