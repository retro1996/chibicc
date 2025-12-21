#include "test.h"

enum __attribute__((__flag_enum__)) FileMode {
    FM_READ  = 1 << 0,
    FM_WRITE = 1 << 1,
    FM_EXEC  = 1 << 2
};


typedef enum __attribute__((__flag_enum__)) {
    OPT_A = 1,
    OPT_B = 2,
    OPT_C = 4
} Options;

Options enable_all(void) {
    return OPT_A | OPT_B | OPT_C;
}

enum  __attribute__((__flag_enum__)) Flags {
    F1 = 1,
    F2 = 2
};

int f(enum Flags x) {
    return x & F1;
}


enum __attribute__((packed, __flag_enum__)) Flags2 {
    A = 1,
    B = 2
};

int use(enum Flags2 f) {
    return f | A;
}


int can_write(enum FileMode m) {
    return (m & FM_WRITE) != 0;   
    
}

int main(void) {
    enum FileMode mode = FM_READ | FM_WRITE;
    ASSERT(1, can_write(mode));
    mode = FM_READ | FM_EXEC;
    ASSERT(0, can_write(mode));
    ASSERT(OPT_A | OPT_B | OPT_C, enable_all());
    ASSERT(1, f(F1));
    ASSERT(0, f(F2));
    ASSERT(3, use(B));
    printf("OK\n");
    return 0;
}
