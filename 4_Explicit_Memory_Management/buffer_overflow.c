#include <stdlib.h>

int main(void){ 
  int *a = (int*)malloc(10 * sizeof(int));
  int c = 0;

  for(c = 0; c < 100; c++){
    a[c] = c;
  }

  return 0;
}
