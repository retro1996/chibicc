#include "test.h"
int main(int argc, char**argv) {

    void *p = 0;
  printf("%d\n", _Generic(argc ? p : "a", void*:1, char*:2 )); // expect 1, got 1
  printf("%d\n", _Generic(argc ? "a" : p, void*:1, char*:2 )); // expect 1, got 2
  ASSERT(1, _Generic(argc ? p : "a", void*:1, char*:2 ));
  ASSERT(1, _Generic(argc ? "a" : p, void*:1, char*:2 ));

  printf("%d\n", sizeof(argc ? "a" : 0)); // expect 8, got 8
  printf("%d\n", sizeof(argc ? 0 : "a")); // expect 8, got 4
  ASSERT(8, sizeof(argc ? "a" : 0));
  ASSERT(8, sizeof(argc ? 0 : "a"));

  printf("OK\n");
}