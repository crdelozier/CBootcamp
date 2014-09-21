#include "binary_tree.h"

#include <assert.h>
#include <stdlib.h>

node *get_new_node(void *data){
  node *new_node = (node*)malloc(sizeof(node));
  new_node->_data = data;
  new_node->_left = NULL;
  new_node->_right = NULL;
}

void insert_node(tree *t, node *n, void *data){
  if(t->compare(n->_data,data) > 0){
    if(n->_left == NULL){
      node *new_node = get_new_node(data);
      n->_left = new_node;
    }else{
      insert_node(t,n->_left,data);
    }
  }else if(t->compare(n->_data,data) < 0){
    if(n->_right == NULL){
      node *new_node = get_new_node(data);
      n->_right = new_node;
    }else{
      insert_node(t,n->_right,data);
    }
  }else{
    // Do not insert if already in the tree
  }
}

void insert(tree *t, void *data){
  assert(t != NULL);

  if(t->_root == NULL){
    node *new_node = get_new_node(data);
    t->_root = new_node;
  }else{
    insert_node(t, t->_root,data);
  }
}

void remove_node(tree *t, void *data){

}

bool contains_node(tree *t, node *n, void *data){
  if(n == NULL){
    return false;
  }

  if(t->compare(n->_data,data) == 0){
    return true;
  }

  if(t->compare(n->_data,data) > 0){
    return contains_node(t,n->_left,data);
  }else{
    return contains_node(t,n->_right,data);
  }
}

bool contains(tree *t, void *data){
  assert(t != NULL);

  if(t->_root == NULL){
    return false;
  }else{
    return contains_node(t,t->_root,data);
  }
}

bool is_empty(tree *t){
  assert(t != NULL);
  return t->_root == NULL;
}
