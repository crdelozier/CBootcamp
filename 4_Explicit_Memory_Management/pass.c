#include <stdio.h>

typedef struct point_t{
  int x;
  int y;
} point;

void by_value(point p){
  p.x = 1;
  printf("(%d,%d)\n",p.x,p.y);
}

void by_reference(point *p){
  p->x = 1;
  (*p).x = 1;
  printf("(%d,%d)\n",p->x,p->y);
}

int main(void){ 
  point p;

  p.x = 0;
  p.y = 0;

  by_value(p);
  printf("(%d,%d)\n",p.x,p.y);

  by_reference(&p);
  printf("(%d,%d)\n",p.x,p.y);

  return 0;
}
