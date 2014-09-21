#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void ignore_for_now(){
  time_t timer;
  time(&timer);
  srand(timer);
}

int main(void){ 
  srand(3);
  int same = rand() % 100; // 0-99
  printf("%d\n",same);

  ignore_for_now();
  int different = rand() % 100;
  printf("%d\n",different);

  return 0;
}
