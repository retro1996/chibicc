#include <stdio.h>

void recursive(int depth, char *start_addr) {
    char local;
    if (depth == 0) {
        start_addr = &local;
    }
    
    if (depth < 10) {
        recursive(depth + 1, start_addr);
    } else {
        printf("Stack usage for 10 calls: %ld bytes\n", start_addr - &local);
        printf("Average stack usage per call: %ld bytes\n", (start_addr - &local) / 10);
    }
}

int main() {
    char local;
    recursive(0, &local);
    return 0;
}
