#include <stdbool.h>
#include <stdint.h>
#include "test.h"

int main() {
    uint32_t target = 0x12345678;
    uint32_t expected = 0x12345678;
    uint32_t desired = 0xDEADBEEF;
    
    // This should update target to 0xDEADBEEF.
    // If chibicc generates a byte operation (due to the bug where it uses the bool return type size),
    // it might generate `lock cmpxchgb %cl, (%rdi)`.
    // If target is 32-bit, we expect `lock cmpxchgl %ecx, (%rdi)`.
    
    bool ret = __atomic_compare_exchange_n(&target, &expected, desired, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    
    if (!ret) printf("FAIL: ret is false\n");
    if (target != 0xDEADBEEF) printf("FAIL: target is 0x%x (expected 0xDEADBEEF)\n", target);
    if (expected != 0x12345678) printf("FAIL: expected is 0x%x\n", expected);
       
    // Test failure case: expected value does not match
    expected = 0xCAFEBABE; 
    ret = __atomic_compare_exchange_n(&target, &expected, 0x0, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    
    if (ret) printf("FAIL: ret is true (should be false)\n");
    // Should update expected to current target value
    if (expected != target) printf("FAIL: expected is 0x%x (should be 0x%x)\n", expected, target);
    ASSERT(target, expected);
    printf("OK\n");
    return 0;
}
