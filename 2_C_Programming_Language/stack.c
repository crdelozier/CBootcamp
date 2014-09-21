#include <stdio.h>

int f(int x, int y){
  x = x * 2;
  y = x + y;
  return x;
}

int main(){
  int x = 7;
  int y = 42;
  y = f(x,y);
  printf("%d\n",y);
  return 0;
}
