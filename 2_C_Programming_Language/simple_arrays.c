#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
  int val = 0;
  if (1) {
    printf("Eh!\n");
  }
  if (true) {
    printf("Good...\n");
  }
  if (val = 0) {
    printf("Doesn't fire...\n");
  }
  return 0;
}
