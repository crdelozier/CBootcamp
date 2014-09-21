#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void){ 
  int *p = (int*)malloc(sizeof(int));
  free(p);

  int *p2 = (int*)malloc(sizeof(int));
  *p2 = 1;

  *p = 5;

  assert(p == p2);

  printf("%d\n",*p2);

  return 0;
}
