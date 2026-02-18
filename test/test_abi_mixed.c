#include <stdio.h>
#include <stdlib.h>

struct T {
    char data[40];
};

void callee(void *it, struct T t, const char *ls, void *line, int lc, long ln, long eln, long *co, long *eco) {
    printf("callee: it=%p, ls=%p, line=%p, lc=%d, ln=%ld, eln=%ld, co=%p, eco=%p\n",
           it, ls, line, lc, ln, eln, co, eco);
    if (co == NULL || eco == NULL) {
        printf("FAIL: NULL pointers detected!\n");
        exit(1);
    }
    *co = 123;
    *eco = 456;
}

int main() {
    struct T t;
    for (int i = 0; i < 40; i++) t.data[i] = i;
    long co = 0, eco = 0;
    void *dummy_it = (void*)0x1111;
    const char *dummy_ls = (void*)0x2222;
    void *dummy_line = (void*)0x3333;
    
    callee(dummy_it, t, dummy_ls, dummy_line, 5, 10, 20, &co, &eco);
    
    if (co == 123 && eco == 456) {
        printf("SUCCESS\n");
        return 0;
    }
    printf("FAIL: co=%ld, eco=%ld\n", co, eco);
    return 1;
}
