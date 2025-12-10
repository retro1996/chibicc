#include "test.h"

typedef short v8hi __attribute__((vector_size(16)));

int main() {
  // Test __builtin_ia32_phaddw128
  // phaddw adds adjacent 16-bit values, so:
  // [a0, a1, a2, a3, a4, a5, a6, a7] + [b0, b1, b2, b3, b4, b5, b6, b7]
  // = [a0+a1, a2+a3, a4+a5, a6+a7, b0+b1, b2+b3, b4+b5, b6+b7]
  
  v8hi a = {1, 2, 3, 4, 5, 6, 7, 8};
  v8hi b = {10, 20, 30, 40, 50, 60, 70, 80};
  
  v8hi result = __builtin_ia32_phaddw128(a, b);
  
  for (int i = 0; i < 8; i++) {
    printf("%d ", (int)result[i]);
  }
  
  // Expected: [3, 7, 11, 15, 30, 70, 110, 150]
  // a0+a1=1+2=3, a2+a3=3+4=7, a4+a5=5+6=11, a6+a7=7+8=15
  // b0+b1=10+20=30, b2+b3=30+40=70, b4+b5=50+60=110, b6+b7=70+80=150
  
  ASSERT(3, result[0]);
  ASSERT(7, result[1]);
  ASSERT(11, result[2]);
  ASSERT(15, result[3]);
  ASSERT(30, result[4]);
  ASSERT(70, result[5]);
  ASSERT(110, result[6]);
  ASSERT(150, result[7]);
  
  printf("OK\n");
  return 0;
}
