The C Programming Language
==========

* Now that we've looked at a few simple examples, let's dive into the basic
  data types that the C programming language provides.

``` c
#include <stdio.h>

int main(void) {
    printf("%d\n",sizeof(char));
    printf("%d\n",sizeof(short));
    printf("%d\n",sizeof(int));
    printf("%d\n",sizeof(long));

    printf("%d\n",sizeof(float));
    printf("%d\n",sizeof(double));

    return 0;
}
```

* Like most languages, C contains built-in data-types for integers and 
  floating-point numbers.  These have various sizes, as demonstrated by the 
  `sizeof` function in the code example.  `char` is not explicitly an 
  integer data type, but it can be used to hold byte-sized data on most 
  systems.

* As you may have noticed, there is no similar type to Java's `boolean` in the
  previous code sample.  C does not explicitly provide a boolean type, as shown 
  in the following example ([bool.c](bool.c)):

``` c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    int val = 0;
    if (1) {
        printf("Eh!\n");
    }
    if (true) {
        printf("Good...\n");
    }
    if (val = 0) {
        printf("Doesn't fire...\n");
    }
    return 0;
}
```

* Unlike Java, C does not have a built-in boolean type.  Instead, numeric values
  operate as booleans where the **value zero** denotes false and any **non-zero
  value** denotes true.

  * As a convenience, you can include `stdbool.h` which defines `bool`, `true`,
  and `false` to be `int` (really `_Bool` but it is morally a numeric type),
  `1`, and `0`, respectively.

  * For example, this makes confusing `=` and `==` within a if-statement even
    more dangerous.  The result of an assignment is the value being assigned, so
    the example above compiles without error but performs unexpectedly!

* Like most languaegs, C also provide arrays.  In C, arrays can be either 
  stack-allocated or heap-allocated.  In future sections, we'll cover the 
  difference and trade-offs between these two types of arrays.  In this 
  example, we examine how to declare a stack-allocated array in C.
  [simple_arrays.c](simple_arrays.c).

``` c
#include <stdio.h>

int main(void) {
    int arr [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }
    return 0;
}
```

* If you are familiar with Java, you have a leg up here as it is a *C-like*
  language.  Programming-in-the-small basics, e.g., variable declarations, basic
  types, for-loops, and arrays, all transfer with some minor differences:

  + The declaration of `arr` is the declaration of a *stack-allocated* array in
    C.  In Java, you would flip the position of the brackets and write `int[]
    arr = { 1, ..., 10 };`.  There is a subtle, yet very important distinction
    here in that the Java array is (always) *heap-allocated* which we will visit
    later in these notes.

  + Note that we declare `i` on a line separate from the head of the `for` loop.
    This is our first example of writing *safely standards compliant* code.  C
    compilers typically support many different versions of the C language.
    Typically the default compilation mode for most compilers is the *C89*
    version of the spec which says that all local variables must be declared at
    the top of the *scope blocks* they are declared in (i.e., each block
    enclosed by curly braces).  To be safe, we respect this rule, but if you
    know your compiler supports declaration of variable like in Java, e.g., C89
    with GNU extensions (the gcc default) or later versions of the standard, you
    can declare locals in the same plaecs as you would in Java.

* C also provides `structs` for grouping data-types together into a
  data structure.  However, since C is a procedural language and not an 
  object-oriented language, these data structures do not have any methods 
  associated with the data.  They are simply a convenient mechanism for 
  grouping related pieces of data.  The following example demonstrates how
  to declare and use structures. [structs.c](structs.c).

```
#include <stdio.h>

struct point_t{
    int x;
    int y;
};

int main(void){
    struct point_t p;
    p.x = 1;
    p.y = 2;

    printf("(%d,%d)\n",p.x,p.y);

    return 0;
}
```

* In this example, we declare a point structure with two integers (an x and 
  y coordinate).  This `struct` is simply a more convenient way to group 
  pieces of data together.