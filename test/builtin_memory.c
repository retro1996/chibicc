#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char buf1[100];
  char buf2[100];
  char *res;

  // Test memcpy return value
  strcpy(buf1, "hello world");
  res = __builtin_memcpy(buf2, buf1, 12);
  if (res != buf2) {
    printf("memcpy return value failed: expected %p, got %p\n", buf2, res);
    exit(1);
  }
  if (strcmp(buf2, "hello world") != 0) {
    printf("memcpy content failed\n");
    exit(1);
  }

  // Test memset return value
  res = __builtin_memset(buf1, 'x', 5);
  if (res != buf1) {
    printf("memset return value failed: expected %p, got %p\n", buf1, res);
    exit(1);
  }
  if (memcmp(buf1, "xxxxx", 5) != 0) {
    printf("memset content failed\n");
    exit(1);
  }

  // Test memset value truncation (should use unsigned char cast of value)
  __builtin_memset(buf1, 0x12345678, 5);
  if ((unsigned char)buf1[0] != 0x78) {
     printf("memset value truncation failed: expected 0x78, got 0x%x\n", (unsigned char)buf1[0]);
     exit(1);
  }

  // Test chained calls
  // memset returns buf1, which is passed to memcpy as dest
  // memcpy returns buf1
  res = __builtin_memcpy(__builtin_memset(buf1, 'y', 10), "123", 4);
  if (res != buf1) {
    printf("chained return value failed\n");
    exit(1);
  }
  if (memcmp(buf1, "123\0yyyyyy", 10) != 0) {
    printf("chained content failed: %s\n", buf1);
    exit(1);
  }

  printf("OK\n");
  return 0;
}