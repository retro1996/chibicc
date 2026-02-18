#include "test.h"

typedef void (*func_t)(void);

void callback(void) {
    printf("Callback executed\n");
}

struct S {
    func_t f;
};

struct S global_s;

void set_callback(func_t f) {
    global_s.f = f;
}

int main() {
    set_callback(callback);
    
    if (global_s.f != callback) {
        printf("Fail: global_s.f != callback\n");
        exit(1);
    }
    
    global_s.f();
    printf("OK\n");
    return 0;
}
