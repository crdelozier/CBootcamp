#pragma once

typedef struct node_t{
  void *_data;
  struct node_t *_next;
} node;

typedef struct list_t{
  struct node_t *_start;
} list;

void push_front(list *list, void *data);
void push_back(list *list, void *data);

void* pop_front(list *list);
void* pop_back(list *list);

int length(list *list);
int is_empty(list *list);
