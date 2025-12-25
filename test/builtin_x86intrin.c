#include "test.h"
#include <stdint.h>
#include <x86intrin.h>
//#include <cetintrin.h>
//#include <x86gprintrin.h> 

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
    __builtin_ia32_vzeroall();
    __builtin_ia32_vzeroupper();
    __builtin_ia32_femms();
    __builtin_ia32_writeeflags_u64(0x200);
    unsigned long long x = 0x201;
    __builtin_ia32_writeeflags_u64(x);
    __builtin_ia32_incsspq(x);
    void *ptr;
    __builtin_ia32_rstorssp(ptr);
    __builtin_ia32_clrssbsy(1);
    int val = 1;
    __builtin_ia32_clrssbsy(val);    
}

unsigned int f7(void) {
    return __builtin_ia32_rdpid();
}

unsigned int f8(void) {
    return __builtin_ia32_rdfsbase32();
}

unsigned long long f9(void) {
    return __builtin_ia32_rdfsbase64();
}

unsigned int f10(void) {
    return __builtin_ia32_rdgsbase32();
}

unsigned long long f11(void) {
    return __builtin_ia32_rdgsbase64();
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


static inline void wrssd(uint32_t *p, uint32_t v) {
    __builtin_ia32_wrssd(p, v);
    __builtin_ia32_wrssq(p, v);
    __builtin_ia32_wrussd(p, v);
    __builtin_ia32_wrussq(p, v);
}

__attribute__((noinline))
void test(uint32_t *p) {
    wrssd(p, 0xdeadbeef);
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
    int x = 0x80000000;   // bit 31 set
    int y = 0x00000100;   // bit 8 set
    int z = 0x00000001;   // bit 0 set

    printf("%d\n", __builtin_ia32_bsrsi(x)); // expected 31
    ASSERT(31, __builtin_ia32_bsrsi(x));
    printf("%d\n", __builtin_ia32_bsrsi(y)); // expected 8
    ASSERT(8, __builtin_ia32_bsrsi(y));
    printf("%d\n", __builtin_ia32_bsrsi(z)); // expected 0
    ASSERT(0, __builtin_ia32_bsrsi(z));
    uint32_t aux1, aux2;
    uint64_t tsc1, tsc2;
    tsc1 = __builtin_ia32_rdtscp(&aux1);
    tsc2 = __builtin_ia32_rdtscp(&aux2);
    if (tsc2 <= tsc1) {
        printf("Warning: TSC did not increase\n");
    }
    printf("TSC1 = %lu, AUX1 = %u\n", tsc1, aux1);
    printf("TSC2 = %lu, AUX2 = %u\n", tsc2, aux2);
    printf("OK\n");
    return 0;
}
