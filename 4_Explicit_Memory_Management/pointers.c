#include <stdio.h>

int main(void){ 
  int x = 0;
  int *p = &x;

  *p = 1;

  printf("%d\n",x);

  return 0;
}
