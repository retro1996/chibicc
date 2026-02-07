#include <stdio.h>

void recursive(int depth, char *start_addr) {
    char local;
    if (depth == 0) {
        start_addr = &local;
    }
    
    if (depth < 120000) {
        recursive(depth + 1, start_addr);
    } else {
        printf("Stack usage for 120000 calls: %ld bytes\n", start_addr - &local);
        printf("Average stack usage per call: %ld bytes\n", (start_addr - &local) / 120000);
    }
}

int main() {
    char local;
    recursive(0, &local);
    return 0;
}
