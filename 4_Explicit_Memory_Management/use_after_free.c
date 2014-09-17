#include <stdlib.h>

int main(void){ 
  int *p = (int*)malloc(sizeof(int));
  free(p);

  *p = 5;

  return 0;
}
