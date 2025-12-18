
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


void f(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int a = va_arg(ap, int);
  int b = va_arg(ap, int);
  int c = va_arg(ap, int);
  printf("a=%d b=%d c=%d\n", a, b, c);
  va_end(ap);
}

int main(void) {
  struct termios t;
  tcgetattr(0, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &t);
  printf("echo off\n");
  sleep(1);
  t.c_lflag |= ECHO;
  tcsetattr(0, TCSANOW, &t);
  printf("echo on\n");
  _Bool x = 1;
  char y = 2;
  short z = 3;
  f("%d %d %d", x, y, z);
  printf("%*d\n", 10, 42);
  printf("%.*f\n", 3, 3.14159);
  printf("ok\n");
}

