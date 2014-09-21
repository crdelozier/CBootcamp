#include "linked_list.h"

#include <stdlib.h>
#include <assert.h>

/*
 * node: int _data, node *_next
 * list: node *_start
 */

node* get_new_node(){
  node *new_node = (node*)malloc(sizeof(node));
  new_node->_next = NULL;
  new_node->_data = 0;
  return new_node;
}

void push_front(list *l, void *data){
  assert(l != NULL);
  node *new_node = get_new_node();
  new_node->_data = data;

  if(l->_start == NULL){
    l->_start = new_node;
  }else{
    node *old_start = l->_start;
    l->_start = new_node;
    new_node->_next = old_start;
  }
}

void push_back(list *l, void *data){
  assert(l != NULL);
  node *new_node = get_new_node();
  new_node->_data = data;

  if(l->_start == NULL){
    l->_start = new_node;
    return;
  }

  node *last_node = l->_start;
  node *current_node = last_node->_next;

  while(current_node != NULL){
    last_node = current_node;
    current_node = last_node->_next;
  }

  last_node->_next = new_node;
}

void* pop_front(list *l){
  void *data;
  assert(l != NULL);
  assert(!is_empty(l));

  node *old_start = l->_start;
  l->_start = old_start->_next;
  data = old_start->_data;
  free(old_start);

  return data;
}

void* pop_back(list *l){
  void *data;
  assert(l != NULL);
  assert(!is_empty(l));

  if(l->_start->_next == NULL){
    data = l->_start->_data;
    free(l->_start);
    l->_start = NULL;
    return data;
  }

  node *last_node = l->_start;
  node *current_node = last_node->_next;

  while(current_node->_next != NULL){
    last_node = current_node;
    current_node = last_node->_next;
  }

  last_node->_next = NULL;
  data = current_node->_data;
  free(current_node);

  return data;
}

int length(list *l){
  int len = 0;
  
  if(l == NULL){
    return 0;
  }

  node *current_node = l->_start;

  while(current_node != NULL){
    current_node = 
      current_node->_next;
    ++len;
  }

  return len;
}

int is_empty(list *l){
  return l->_start == NULL;
}
