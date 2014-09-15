#include <stdio.h>

struct point_t{
  int x;
  int y;
};

int main(void){
  struct point_t p;
  p.x = 1;
  p.y = 2;

  printf("(%d,%d)\n",p.x,p.y);

  return 0;
}
