#include "linked_list.h"

#include <stdlib.h>

node* get_new_node(void *data){
  node *new_node = (node*)malloc(sizeof(node));
  new_node->_data = data;
  new_node->_next = NULL;
  return new_node;
}

node* find_last_node(node *start){
  node *current_node = start;
  while(current_node->_next != NULL){
    current_node = current_node->_next;
  }
  return current_node;
}

void push_front(list *l, void *data){
  node *new_node = get_new_node(data);
  if(l->_start == NULL){
    l->_start = new_node;
  }else{
    new_node->_next = l->_start;
    l->_start = new_node;
  }
}

void push_back(list *l, void *data){
  node *new_node = get_new_node(data);
  if(l->_start == NULL){
    l->_start = new_node;
  }else{
    node *last_node = find_last_node(l->_start);
    last_node->_next = new_node;
  }
}

void* pop_front(list *l){
  void *data;
  if(is_empty(l)){
    return NULL;
  }

  node *old_start = l->_start;
  l->_start = old_start->_next;
  data = old_start->_data;
  free(old_start);

  return data;
}

void* pop_back(list *l){
  void *data;
  node *current_node = l->_start;
  node *last_node = NULL;

  if(is_empty(l)){
    return NULL;
  }

  if(length(l) == 1){
    current_node = l->_start;
    data = current_node->_data;
    l->_start = NULL;
    free(current_node);
    return data;
  }

  while(current_node->_next != NULL){
    last_node = current_node;
    current_node = current_node->_next;
  }

  data = current_node->_data;
  last_node->_next = NULL;
  free(current_node);

  return data;
}

int length(list *l){
  node *current_node = l->_start;
  int len = 0;
  while(current_node != NULL){
    current_node = current_node->_next;
    len++;
  }
  return len;
}

int is_empty(list *l){
  return l == NULL || l->_start == NULL;
}
