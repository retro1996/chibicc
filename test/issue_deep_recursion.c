#include <stdio.h>

int recursive(int n) {
    if (n == 0) {
        return 0;
    }
    // This expression will likely use temporary stack space
    int result = (n * 123 + 456) / 789;
    return recursive(n - 1) + result;
}

int main() {
    // A moderately deep recursion
    int result = recursive(1000);
    printf("Result: %d\n", result);
    return 0;
}