#include <stdio.h>
#include <stdlib.h>

int main(){
  char *str = "Test";
  int c = 0;
  char str2[] = {'T','e','s','t','\0'};

  char strnum2[] = {'3','2'};
  char strnum1[] = {'1','1','\0'};

  for(c = 0; c < 5; c++){
    printf("%c",str[c]);
  }
  printf("\n");

  printf("%s\n",str2);

  printf("%d\n",atoi(strnum1));
  printf("%d\n",atoi(strnum2));

  return 0;
}
