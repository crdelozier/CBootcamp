#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

int main(){
  int *a = (int*)malloc(SIZE * sizeof(int));
  int *b = (int*)malloc(SIZE * sizeof(int));
  int *c = (int*)malloc(SIZE * sizeof(int));
  int i = 0;

  for(i = 0; i < SIZE; i++){
    a[i] = i;
  }

  memset(b,0,SIZE * sizeof(int));
  memset(c,0,SIZE * sizeof(int));

  memcpy(b,a,SIZE * sizeof(int));
  memmove(c,a,SIZE * sizeof(int));

  if(memcmp(a,b,SIZE * sizeof(int)) == 0){
    printf("A and B are the same!\n");
  }

  if(memcmp(b,c,SIZE * sizeof(int)) == 0){
    printf("B and C are the same!\n");
  }

  return 0;
}
