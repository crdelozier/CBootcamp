#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s [number]\n", argv[0]);
  } else {
    int val = atoi(argv[1]);
    if (val == 100) {
      printf("That's a good number!\n");
    } else {
      printf("%d is a bad number! Do not enter %d!\n", val);
    }
  }
  return 0;
}
