#include <stdio.h>

typedef int error_code;

typedef double currency;
typedef double velocity;


struct point_t{
  int x;
  int y;
};

typedef struct point_t point;

int main(void){
  point p;

  point arr[10];

  int xs[10];
  int ys[10];

  p.x = 1;
  p.y = 2;

  printf("(%d,%d)\n",p.x,p.y);

  return 0;
}
