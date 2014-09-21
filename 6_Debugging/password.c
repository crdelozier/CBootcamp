#include <stdio.h>
#include <stdlib.h>

int main(){
  int password = rand() % 100000;
  int p = 0;
  char buffer[100];

  printf("Please enter the password: ");
  
  fgets(buffer,100,stdin);
  p = atoi(buffer);

  if(p == password){
    printf("Good job!\n");
  }else{
    printf("Incorrect, please try again!\n");
  }

  return 0;
}
