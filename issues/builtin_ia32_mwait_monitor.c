#include "test.h"
#include <stdint.h>
#include <mwaitintrin.h>

int main() {
    volatile int data = 0;

    // Address to monitor
    void *addr = &data;

    unsigned int ext = 0;
    unsigned int hints = 0;

    // Monitor the address
    __builtin_ia32_monitor(addr, ext, hints);

    // Wait until the monitored address is written to
    __builtin_ia32_mwait(ext, hints);

    // Write something afterwards
    data = 42;
    printf("Data after MWAIT: %d\n", data);
    printf("OK\n");

    return data;
}
