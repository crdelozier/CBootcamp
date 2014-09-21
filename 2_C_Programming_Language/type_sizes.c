#include <stdio.h>

int main(void) {
  printf("%d\n",sizeof(char));  // 1
  printf("%d\n",sizeof(short int)); // 2
  printf("%d\n",sizeof(int)); // 4
  printf("%d\n",sizeof(long int)); // 8

  printf("%d\n",sizeof(unsigned int));

  printf("%d\n",sizeof(float)); // 4
  printf("%d\n",sizeof(double)); // 8

  return 0;
}
