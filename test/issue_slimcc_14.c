#include "test.h"

// file scope
int arr[2][2] = {{1,2},{3,4}};
int *p1 = arr[1];
int fcast = (float)16777217.0;

int main(int argc, char**argv){
  char arr[3] = {11, 22, 33};
  int i;
  i = (&arr)[0][2], printf("%d\n", i); // 33
  i = (*&arr)[1], printf("%d\n", i); // 22
  i = (**&arr), printf("%d\n", i); // 11
  ASSERT(33, (&arr)[0][2]);
  ASSERT(22, (*&arr)[1]);
  ASSERT(11, (**&arr));
  struct { int i:5; _Bool b:1;} s = {.b = 1};
  int j = s.b; 
  printf("%d\n",j); // expect 1, got -1
  ASSERT(1, j);
    switch(0x123456789) { 
    case 0x123456789:
      printf("expected branch\n");
      break;
    default:   
      printf("wrong branch\n");
  }

    struct {
      unsigned field :8;
    } bit = {0};
    
    printf("%d\n", bit.field > -1 ); // expect true, got false
  ASSERT(1, bit.field > -1);
    int k = 0;
    int arr[(k++, 4)];
    printf("%d\n", k); // expect 1, got 0
    ASSERT(1, k);
     _Bool x,y,b;
 b = 1;
 printf("bb plus\n");
 x = b;
 y = b++;
 printf("%d\n", x == y); //expect true, got false
ASSERT(1, x == y);
 b = 0;
 printf("bb minus\n");
 x = b;
 y = b--;
 printf("%d\n", x == y); //expect true, got false
ASSERT(1, x == y);
 printf("%d\n", fcast);  // expect 16777216, got 16777217
  ASSERT(16777216, fcast);
  printf("OK\n");
  return 0;
}