#include "compare.h"

int int_compare(void *p1, void *p2){
  int i1 = (int)p1;
  int i2 = (int)p2;

  if(i1 > i2){
    return 1;
  }else if(i1 < i2){
    return -1;
  }else{
    return 0;
  }
}
