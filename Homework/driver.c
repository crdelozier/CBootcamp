#include "binary_tree.h"
#include "compare.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
  tree *t = (tree*)malloc(sizeof(tree));
  t->_root = NULL;
  t->compare = int_compare;

  assert(is_empty(t));

  insert(t,(void*)5);
  insert(t,(void*)2);
  insert(t,(void*)1);
  insert(t,(void*)8);
  insert(t,(void*)7);

  assert(!is_empty(t));

  assert(contains(t,(void*)1));
  assert(contains(t,(void*)2));
  assert(contains(t,(void*)5));
  assert(contains(t,(void*)7));
  assert(contains(t,(void*)8));

  remove_node(t,(void*)7);
  remove_node(t,(void*)5);

  assert(!contains(t,(void*)5));
  assert(!contains(t,(void*)7));

  printf("All tests passed!\n");

  return 0;
}
