#include <stdio.h>
#include <stdlib.h>

int sum(int *A, unsigned int length){
  int s = 0;
  unsigned int c = 0;
  for(c = 0; c < length; c++){
    s += A[c];
  }
  return s;
}

int main(){
  int size = 20;
  int *A = (int*)malloc(size * sizeof(int));
  int c = 0;
  int s = 0;

  for(c = 0; c < size; c++){
    A[c] = c;
  }

  s = sum(A,size);
  printf("%d\n",s);

  return 0;
}
