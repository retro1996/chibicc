#include <stdio.h>
int main(int argc, char**argv) {
  char _Alignas(1024) lvar;
  short _Alignas(2048) vla[argc];
  printf("%d, %d\n", 1023 & (int)&lvar, 2047 & (int)&vla); // expect 0,0
  return 0;
}
