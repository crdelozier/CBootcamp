#include <stdio.h>
#include <stdlib.h>

typedef struct point_t{
  int x;
  int y;
} point;

int main(){
  size_t num;
  point p1;
  point p2;
  FILE *file;

  p1.x = 5;
  p1.y = 7;

  file = fopen("test.bin","wb");

  if(file == NULL || ferror(file) != 0){
    return 1;
  }

  num = fwrite(&p1,sizeof(point),1,file);

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  fclose(file);

  file = fopen("test.bin","rb");

  if(file == NULL || ferror(file) != 0){
    return 1;
  }

  num = fread(&p2,sizeof(point),1,file);

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  printf("(%d,%d)\n",p2.x,p2.y);

  fclose(file);

  return 0;
}
