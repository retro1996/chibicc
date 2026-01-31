#include <stdio.h>

long double fn(void) {
  asm("fninit");
  return 2.0L;
}
long double fn2 (long double a) {
  return  a + (a + (a + (a + (a + (a + (a + (a + a)))))));
}
int main(void) {
  printf("%Lf\n", 3.0L + fn() + 5.0L); // expected 10.0
  printf("%Lf\n", 3.0L + fn2(7.0L) + 5.0L); // expected 71.0
}