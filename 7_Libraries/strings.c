#include <string.h>
#include <stdio.h>

int main(){
  char buf[100];
  char *tok;

  strncpy(buf,"Hello world!",13);
  printf("%s\n",buf);

  strncat(&buf[12]," Hello again!",14);
  printf("%s\n",buf);

  if(strncmp(buf,"Hello",5) == 0){
    printf("They match\n");
  }

  printf("String length: %d\n",strlen(buf));
  printf("%s\n",strchr(buf,'!'));
  printf("%s\n",strstr(buf,"world"));

  tok = strtok(buf,"!");
  printf("%s\n",tok);
  tok = strtok(NULL,"!");
  printf("%s\n",tok);

  return 0;
}
