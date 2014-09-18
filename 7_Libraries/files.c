#include <stdio.h>

int main(){
  FILE *file = fopen("test.txt","w");
  char buf[100];
  int num = 0;

  // Check to see if the file was created or not
  if(file == NULL || ferror(file) != 0){
    return 1;
  }

  num = fprintf(file,"Hello!\n");

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  fclose(file);

  file = fopen("test.txt","r");

  if(file == NULL || ferror(file) != 0){
    return 1;
  }

  num = fscanf(file,"%s",buf);

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  printf("%s\n",buf);

  return 0;
}
