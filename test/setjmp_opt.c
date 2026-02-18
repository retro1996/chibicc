#include "test.h"
#include <setjmp.h>

static jmp_buf env;

void recurse(int n) {
    // Use some temporaries to stress stack usage
    int a = n * 10;
    int b = n * 20;
    
    if (n == 0) {
        longjmp(env, 1);
    }
    
    recurse(n - 1);
    
    // This part is unreachable due to longjmp, but ensures temporaries are live across call
    ASSERT(0, a + b); 
}

int main() {
    if (setjmp(env) == 0) {
        recurse(100);
    }
    
    printf("OK\n");
    return 0;
}