#include <stdio.h>
#include <stdlib.h>

typedef struct u_entry {
    int val;
    struct u_entry *next;
} u_entry_T;

typedef struct u_header {
    int seq;
    u_entry_T *entries;
    struct u_header *next;
} u_header_T;

// Recursive addition, like Vim
void recursive_addstate(u_header_T **head, int seq, int depth) {
    if (depth <= 0) return;

    u_header_T *h = malloc(sizeof(*h));  // uninitialized memory
    h->seq = seq;
    h->entries = NULL;
    h->next = *head;
    *head = h;

    // Add some entries
    for (int i = 0; i < 3; i++) {
        u_entry_T *e = malloc(sizeof(*e)); // uninitialized
        e->val = seq * 10 + i;
        e->next = h->entries;
        h->entries = e;
    }

    recursive_addstate(head, seq + 1, depth - 1);
}

// Traverse without safety checks
void traverse(u_header_T *head) {
    while (head) {
        u_entry_T *e = head->entries;
        while (e) {
            printf("seq=%d val=%d\n", head->seq, e->val);
            e = e->next;  // SEGFAULT here if memory is corrupt
        }
        head = head->next;
    }
}

int main() {
    u_header_T *undo_list = NULL;

    recursive_addstate(&undo_list, 1, 50); // deeper recursion
    traverse(undo_list);

    return 0;
}
