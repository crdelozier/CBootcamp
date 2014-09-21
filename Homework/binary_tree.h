#pragma once

#include <stdbool.h>

typedef struct node_t{
  void *_data;
  struct node_t *_left;
  struct node_t *_right;
} node;

typedef struct tree_t{
  struct node_t *_root;
  int (*compare)(const void*, const void*);
} tree;

void insert(tree *t, void *data);
void remove_node(tree *t, void *data);
bool contains(tree *t, void *data);

bool is_empty(tree *t);
