#include "multi_cu.h"
#include <stdio.h>

extern int g_num;

void print_num(int n) {
  printf("%d,%d\n",n,g_num);
}
