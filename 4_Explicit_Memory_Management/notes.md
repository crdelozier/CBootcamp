Manual Memory Management
==========

* Programming in C requires explicit care and consideration from the 
  programmer because the programmer must manually manage memory 
  allocations.  In many modern languages, like Java, the programmer
  no longer has to worry about manually managing memory because garbage
  collection handles it for him.  However, this comes at the cost of 
  less control over memory and possibly worse performance.

Pointers
------------

* Up to this point, most of the data-types that we have used have 
  directly stored the type of data specified.  For example, an int
  data-type directly declares and stores an integer.

* Pointers are used to hold the memory address of another piece of 
  data.  In the following program, we demonstrate how pointers can 
  be used to store the address and access the value of an integer
  allocated on the stack. [pointers.c](pointers.c)

```
#include <stdio.h>

int main(void){
    int x = 0;
    int *p = &x;

    *p = 1;

    printf("%d\n",x);

    return 0;
}
```

* Using the C mental model from the last section of notes, we can 
  examine how this program works.  In this version, we show an address 
  for each piece of data stored on the stack.

```
  Stack
  ------
0xFFF0   main
0xFFF4 x [     ]
0xFFF8 p [     ]
```

* The program starts with the structure shown above.  After the first two assignments, 
  the values will update to look like this:

```
  Stack
  ------
0xFFF0   main
0xFFF4 x [ 0 ]
0xFFF8 p [ 0xFFF4 ]
```

* As you can see, the value of 0 is assigned into `x`, and the address 
  of `x` is assigned into `p`.  When we dereference p on the next line of code, 
  the program stores the value 1 into the address held by `p`, which happens
  to be the address of `x`.

* The `*` symbol is used to designate that a variable is a pointer.  In this 
  case, we declare `p` as a pointer to an integer.

* We use the `&` operator to take the address of an expression.  In this example, 
  `&x` provides the address of the local variable x.  We can then store this 
  address in a pointer to use it later in the program.

* The dereference operator uses the same `*` symbol that is used to declare a 
  pointer.  Dereferencing a pointer accesses the memory at the address stored 
  in the pointer.  If the dereference is on the left side of an `=` operator, 
  the value on the right side of the `=` operator will be stored into the address
  pointed to by the pointer.  If the dereference is on the right side, the value
  at the address pointed to by the pointer will be read.

Null pointers
------------

* In the following example, we'll see a few ways in which pointers can cause
  errors in your C programs. [null_pointers.c](null_pointers.c)

```
#include <stdlib.h>

int main(void){
    int *p1;
    int *p2 = NULL;

    *p1 = 0;
    *p2 = 0;

    return 0;
}
```

* If we run this program with gdb (a C/C++ debugger), we'll see that the program 
  fails on the assignment to `p2`, but not on the assignment to `p1`.  `NULL` or 
  `0` is treated as a special value by most operating systems in that it cannot 
  be read or written.  Thus, when we try to dereference a pointer that points to 
  `NULL` on a Unix system, the system will kill the program with a Segmentation 
  Fault error.

* In Java, an attempt to assign into a reference that has not been initialized will 
  generate a `NullPointerException`.  However, in C, variables are not default initialized
  to any value and will simply contain whatever value was in memory at that address.
  These default values are often referred to as "garbage".  Dereferencing a pointer
  that contains "garbage" will lead to unexpected results because the address held 
  by the pointer could point to anything.  These errors are particularly dangerous
  because they are less likely than null-pointer dereferences to produce an error 
  like a Segmentation Fault.  It is important to always initialize pointers in your
  C programs to NULL.

Pass-by-value versus Pass-by-reference
------------

* Function arguments in C can be passed by value or passed by reference.  The following
  code example demonstrates the two possible options. [pass.c](pass.c)

```
#include <stdio.h>

typedef struct point_t{
    int x;
    int y;
} point;

void by_value(point p_f){
    p_f.x = 1;
    printf("(%d,%d)\n",p_f.x,p_f.y);
}

void by_reference(point *p_f){
    p->x = 1;
    printf("(%d,%d)\n",p.x,p.y);
}

int main(void){
    point p;
    
    p.x = 0;
    p.y = 0;
    
    by_value(p);
    printf("(%d,%d)\n",p.x,p.y);

    by_reference(&p);
    printf("(%d,%d)\n",p.x,p.y);

    return 0;
}
```

* In this code, we have one function that takes its parameters by value and 
  one that takes its parameters by reference (as pointers).

* Functions with pass-by-value parameters copy the data from the caller into 
  the function arguments.  In this example, this means that we have 2 copies
  of `p` on the stack when `by_value` is called.  One copy resides in `main`, 
  and the other resides in `by_value`.

```
  Stack
  ------
main
p.x [ ]
p.y [ ]
by_value
p_f.x [ ]
p_f.y [ ]
```

* Functions with pass-by-reference parameters use a pointer to the argument 
  in order to avoid copying the data.  In this example, the `by_reference` 
  function takes a pointer to a point instead of a point.

```
  Stack
  ------
main
p.x [ ]
p.y [ ]
by_reference
p_f [ &p ]
```

* In `by_value`, when we change the value of `x` in `p_f`, the value of 
  `x` in `p` does not change because we are only changing `x` in the copy 
  of `p` that `by_value` owns.

* In `by_reference`, when we change the value of `x` in `p_f`, the value of 
  `x` in `p` also changes because `p.x` is at the same memory address as 
  `p_f->x' (because `p_f` is pointing to `p`).

void*
------------

* C provides the `void*` (void pointer) type in order to allow a programmer 
  to point to memory of an unknown type.  A void pointer cannot be dereferenced, 
  and therefore it must be type-cast to the (hopefully) correct type before
  using it.  A type-cast is of the form:

```
void *v;
int *p = (int*)v;
```

malloc()
------------

* The C programming language standard library provides the `malloc` (short
  for memory allocate) function.  `malloc()` is defined as shown below.

```
void* malloc(size_t size);
```

* As you can see, `malloc()` returns a void pointer.  So, the result of malloc
  must be cast to the correct type before using it.  Some versions of the 
  C programming language will allow implicit conversions from a void pointer
  to the specified pointer type, but it is a best practice to always cast
  the return value of malloc to the correct pointer type.

```
int *p = (int*)malloc(sizeof(int));
```

* Unlike allocating memory using `new` in Java, `malloc()` requires that the 
  programmer calculate the size, in bytes, of the allocated memory.  Thus, 
  when we want to allocate an integer, we need to pass the result of the 
  `sizeof()` function to `malloc()`.  If we instead want to allocate an 
  array of integers, we need to multiply the size of an integer by the 
  number of integers we want to allocate, as follows.

```
int *p = (int*)malloc(10 * sizeof(int));
```

* It is important to check the return value of `malloc()` to make sure 
  that it is not null.  If the return value is `NULL`, the system 
  has run out of memory and is unable to service the program's request.

```
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void){
    int *p = (int*)malloc(sizeof(int));
    assert(p != NULL);
    int *a = (int*)malloc(10 * sizeof(int));
    assert(a != NULL);
    int c = 0;

    for(c = 0; c < 10; c++){
        a[c] = c;
    }

    for(c = 0; c < 10; c++){
        *p += a[c];
    }

    printf("%d\n",*p);

    return 0;
}
```

* This example demonstrates using malloc to allocate both a single 
  integer and an array of integers.  The program then uses both the 
  singleton pointer dereference operator (`*`) and the array indexing 
  operator (`[]`) to access these allocations.  In most cases, you 
  should access arrays using the indexing operator.  However, in 
  some cases, pointer arithmetic can be useful.

* As shown below, we can rewrite the second for-loop to use pointer
  arithmetic instead of array indexing.

```
for(c = 0; c < 10; c++){
    *p += *a;
    a++;
}
```
* Each increment on the pointer `a` adds sizeof(int) to the address
  currently held by `a`, moving it to the next integer in memory.
  We can imaging that the heap looks something like the diagram below.

```
  Heap
  ------
      p    [  ]
a --> a[0] [  ]
      a[1] [  ]
      ...
      a[9] [  ]
```

* After an increment operation, the pointer a would move to the 
  next element in the array, like so.

```
  Heap
  ------
      p    [  ]
      a[0] [  ]
a --> a[1] [  ]
      ...
      a[9] [  ]
```

free()
------------

* As noted in the prior section, if the system runs out of memory, 
  `malloc()` will return a null pointer and possibly cause the program 
  to crash.  To prevent this failure case, the programmer must return 
  memory to the operating system when the program is finished using it.
  This can be accomplished by calling `free()` on a pointer to the 
  memory to be released.  `free()` has the following form.

```
void free(void* ptr);
```

* To demonstrate how to use free correctly, a modified version of the 
  malloc example is shown below with free inserted to return memory 
  to the operating system.

```
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void){
    int *p = (int*)malloc(sizeof(int));
    assert(p != NULL);
    int *a = (int*)malloc(10 * sizeof(int));
    assert(a != NULL);
    int c = 0;

    for(c = 0; c < 10; c++){
        a[c] = c;
    }

    for(c = 0; c < 10; c++){
        *p += a[c];
    }

    printf("%d\n",*p);

    free(p);
    free(a);

    return 0;
}
```

Two-dimensional arrays
------------

* Two-dimensional arrays in C are not declared in the same way as two-dimensional 
  arrays in Java and other languages that support them naturally.  In C, a two
  dimensional array is declared as a pointer to a pointer of the type of the array, 
  as shown below.

```
int **a = (int**)malloc(10 * sizeof(int*));
int c = 0;

for(c = 0; c < 10; c++){
    a[c] = (int*)malloc(10 * sizeof(int));
}
```

* In this code, we create a two-dimensional array of size and type `int[10][10]`.
  Note that in the first call to `malloc()`, we use `sizeof(int*)` instead of 
  `sizeof(int)`.  We do this because the first dimension of the two-dimensional 
  array is holding pointers to the actual int arrays.

* Also note that this two-dimensional array representation is not entirely efficient.
  A two-dimensional array can also be allocated as a single large array and then 
  accessed like normal with two indexing operations.

Memory Safety
------------

* Manual memory management is often prone to bugs.  The most common of these bugs are
  buffer overflow and use-after-free errors.

* Buffer overflows occur when memory outside of the allocated region is accessed.  An 
  example is shown below. [buffer_overflow.c](buffer_overflow.c)

```
#include <stdlib.h>

int main(void){
    int *a = (int*)malloc(10 * sizeof(int));
    int c = 0;

    for(c = 0; c < 100; c++){
        a[c] = c;
    }

    return 0;
}
```

* In this example, we allocate an array of size 10, but then attempt to access
  100 elements of that array.  This example is not particularly dangerous, but 
  if other data had been allocated after the 10 element array, the writes to elements
  10 through 99 would be overwriting other memory.

* When we run this program, it is possible (and even likely) that the program will 
  not crash.  This is because C does not check for out-of-bounds errors like Java 
  does.  Although this is faster, it can lead to dangerous security vulnerabilities
  and hard to track down bugs.  To prevent these sorts of errors, it is recommended 
  that you run a tool like valgrind to find any possible memory safety errors in your
  programs.  We will cover this tool later in the bootcamp.

* The other common memory safety error is use-after-free.  This error is shown in the 
  following example.  [use_after_free.c](use_after_free.c)

```
#include <stdlib.h>

int main(void){
    int *p = (int*)malloc(sizeof(int));
    free(p);

    *p = 5;

    return 0;
}
```

* In this example, we allocate an integer and then immediately free it.  However, we 
  access the integer after it has been freed.  Again, this is not particularly bad in 
  this program, but in other programs, it is possible that the freed memory will be
  reallocated by the operating system.  If this occurs, the access to the freed memory 
  will overwrite memory that it should not overwrite.