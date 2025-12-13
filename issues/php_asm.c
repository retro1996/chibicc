// test_asm_guard.c

#define XXH_COMPILER_GUARD(var) __asm__("" : "+r" (var))

int main(void) {
    int x = 42;
    XXH_COMPILER_GUARD(x);
    return x;
}
