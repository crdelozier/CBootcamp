#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
  list *l = (list*)malloc(sizeof(list));

  assert(is_empty(l));

  push_back(l,(void*)2);
  push_front(l,(void*)1);
  push_back(l,(void*)3);

  assert(length(l) == 3);
  assert(!is_empty(l));

  assert((int)pop_front(l) == 1);
  assert((int)pop_back(l) == 3);
  assert((int)pop_back(l) == 2);

  printf("All tests passed!\n");

  return 0;
}
