#include "test.h"
int main(int argc, char**argv) {
  char _Alignas(128) lvar;
  short _Alignas(32) vla[argc];
  printf("%d, %d\n", 127 & (int)&lvar, 31 & (int)&vla); // expect 0,0
  ASSERT(0, 127 & (int)&lvar);
  ASSERT(0, 31 & (int)&vla);
  return 0;
}