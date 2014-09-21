#include "multi_cu.h"
#define MY_CONSTANT 42

int g_num = 5;

int main(void) {
  print_num(MY_CONSTANT); // print_num(42)
  return 0;
}
