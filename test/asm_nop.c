#include "test.h"


#define ASM_NOP_REPLACE(...) __asm__ volatile(__VA_ARGS__)

int main() {
    int a = 1, b = 2;

    // Empty template (""), simple volatile
    ASM_NOP_REPLACE("");

    // Volatile with memory clobber
    ASM_NOP_REPLACE("" ::: "memory");

    // Rep; nop template
    ASM_NOP_REPLACE("rep; nop" ::: "memory");

    // Single operand, read/write
    ASM_NOP_REPLACE("" : "+r"(a));

    // Two operands, read/write
    ASM_NOP_REPLACE("" : "+r"(a), "+r"(b));

    // Inputs only
    ASM_NOP_REPLACE("" : : "r"(a), "r"(b));

    // Inputs and outputs
    ASM_NOP_REPLACE("" : "+r"(a) : "r"(b));

    // Full three-part extended asm with clobbers
    ASM_NOP_REPLACE("" : "+r"(a) : "r"(b) : "memory");

    printf("Test completed without parsing errors.\n");
    return 0;
}
