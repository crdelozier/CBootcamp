#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int param){
  printf("Null pointer exception!\n");
}

int main(){
  void (*previous_handler)(int);
  int *p = NULL;

  previous_handler = signal(SIGSEGV,handler);

  raise(SIGSEGV);

  return 0;
}
