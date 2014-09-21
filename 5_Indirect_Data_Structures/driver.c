#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct point_t{
  int x;
  int y;
} point;

int main(int argc, char **argv){
  list *l = (list*)malloc(sizeof(list));
  list *l2 = (list*)malloc(sizeof(list));
  point p1;
  point p2;

  l->_start = NULL;
  l2->_start = NULL;

  push_back(l2,(void*)&p1);
  push_back(l2,(void*)&p2);

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

  free(l);
  free(l2);

  return 0;
}
