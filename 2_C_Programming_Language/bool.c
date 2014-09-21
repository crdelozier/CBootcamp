#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // bool, true, false

int main(int argc, char **argv) {
  int val = 0;
  if (1) {
    printf("Eh!\n");
  }
  if (true) { // true = 1
    printf("Good...\n");
  }
  if (val = 0) { // == != > < <= >= if(0){
    printf("Doesn't fire...\n");
  }
  return 0;
}
