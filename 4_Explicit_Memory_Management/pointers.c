#include <stdio.h>

int *p;

/* Globals */
/* -------- */
/* 0x0600 p [ 0xFFF8 ] */

/* Stack */
/* -------- */
/* 0xFFF0 main */
/* 0xFFF4 g */
/* 0xFFF8 y [ 0 ]  */

void f(){
  int x = 1;
  p = &x;
}

void g(){
  int y = 0;
  printf("%d\n",*p);
}

int main(void){ 
  f();
  *p = 1;
  g();

  return 0;
}
