#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int param){
  printf("Null pointer exception!\n");
  exit(1);
}

int main(){
  void (*previous_handler)(int);
  int *p = NULL;

  previous_handler = signal(SIGSEGV,handler);
  *p = 5;

  return 0;
}
