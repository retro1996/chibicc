#include "test.h"
//#include <x86intrin.h>
//#include <cetintrin.h>

void f4(void) {
    __builtin_ia32_saveprevssp();
    __builtin_ia32_setssbsy();
    __builtin_ia32_slwpcb();    
    __builtin_ia32_xend();
    __builtin_ia32_serialize();
    __builtin_ia32_xsusldtrk();
    __builtin_ia32_xresldtrk();
    __builtin_ia32_clui();
    __builtin_ia32_stui();
    __builtin_ia32_testui();
    __builtin_ia32_wbnoinvd();
    __builtin_ia32_xtest();    
    __builtin_ia32_wbinvd();
}

int f5(void) {
    return __builtin_ia32_rdpkru();
}

unsigned int f6(void) {
    return __builtin_ia32_xbegin();
}

unsigned long long f3(void) {
    return __builtin_ia32_rdsspq();
}

unsigned long long f1(void) {
    return __builtin_ia32_rdtsc();
}

unsigned long long f2(void) {
    return __builtin_ia32_readeflags_u64();
}

int main(void) {
    unsigned long long t1 = f1();
    unsigned long long t2 = f1();
    ASSERT(t2 > t1, 1);
    unsigned long long e1 = f2();
    unsigned long long e2 = f2();
    ASSERT(e2 >= e1, 1);
    unsigned long long s1 = f3();
    unsigned long long s2 = f3();
    ASSERT(s2 >= s1, 1);
    unsigned int p1 = f6();
    ASSERT(0, p1);
    printf("OK\n");
    return 0;
}
