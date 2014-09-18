Data Structures
===============

* In this section, we'll cover a few examples of using manual 
  memory management in C to write data structures 
  such as linked lists and trees.  These examples will provide
  a more in-depth overview of how to structure C code, especially 
  when pointers are involved.

* We'll start with two simple structs that will be the basis of 
  our singly linked list.

```
typedef struct node_t{
  int _data;
  struct node_t *_next;
} node;

typedef struct list_t{
  struct node_t *_start;
} list;
```

* Note that we add an underscore before each variable definition 
  in the structs.  This is a common programming practice in C and 
  C++ to differentiate between struct members and local variables.
  Some programmers prefer to use `m_data` and `m_next` instead of 
  just an underscore to indicate that the variable is a member
  variable.  Similarly, global variables can be prefaced with `g_`.

* We'll also define a few functions in the [linked_list.h](linked_list.h)
  header to allow the program to perform some oeprations on this structure.

```
void push_front(list *list, int data);
void push_back(list *list, int data);

int pop_front(list *list);
int pop_back(list *list);

int length(list *list);
int is_empty(list *list);
```

Exercises
---------

* Modify the singly linked-list to allow any data type
  instead of just ints.

* Modify the singly linked-list to instead be a doubly 
  linked list.  This should make the `push_back` and 
  `pop_back` functions much more efficient.

* Create a binary tree data-structure using the same 
  basic principles as the linked-list structure.