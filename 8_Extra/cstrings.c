#include <stdio.h>

int main(){
  char *str = "Test";
  int c = 0;
  char str2[] = {'T','e','s','t','\0'};

  for(c = 0; c < 5; c++){
    printf("%c",str[c]);
  }
  printf("\n");

  printf("%s\n",str2);

  return 0;
}
