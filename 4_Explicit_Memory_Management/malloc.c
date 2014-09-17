#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void){ 
  int *p = (int*)malloc(sizeof(int));
  assert(p != NULL);
  int *a = (int*)malloc(10 * sizeof(int));
  assert(a != NULL);
  int c = 0;

  for(c = 0; c < 10; c++){
    a[c] = c;
  }   

  for(c = 0; c < 10; c++){
    *p += a[c];
  }

  printf("%d\n",*p);

  return 0;
}
