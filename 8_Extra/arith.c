#include <stdlib.h>
#include <stdio.h>

int main(){
  int *a = (int*)malloc(10 * sizeof(int));

  int *a1 = &a[0]; // a1 = a;
  int *a2 = &a[9]; // a2 = a + 9;
  int c = 0;

  for(c = 0; c < 10; c++){
    a[c] = c;
  }
  
  while(a1 < a2){
    int tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;

    ++a1;
    --a2;
  }

  for(c = 0; c < 10; c++){
    printf("%d\n",a[c]);
  }
}
