The C Programming Language
==========

* Now that we've looked at a few simple examples, let's dive into the basic
  data types that the C programming language provides.

C data types
------------

* When designing programs, we describe the real-world data that we work with
  using various *types* that our programming language provides.  For example,
  the collection of students in a class can be represented as a list of strings
  (each string denoting a student's name) or the actors in a simulation can be
  represented as a collection of different objects in an (object-oriented) class
  hierarchy.

* When using C, it pays not to only think of our data in these higher-level
  terms, but also at a lower-level, i.e., how C itself views types.

  * This is because to take advantage of the "close to the metal" nature of C,
    we must know what is going on underneath the hood

  * Also, many of the errors that we face as C programmers can be diagnosed as
    long as we have crisp model in our heads of how C executes.

Fundamental Datatypes
---------------------

* In C, *all data is a collection of bits interpreted in various ways*.  In
  fact, C only distinguishes data on two axes:

  * The datum's size, i.e., how many bytes is it, and
  * How do we interpret these bits?

* To explore the fundamental types in C, we can build a small program that
  inspects the sizes of each type as implmented in
  [basic_types.c](src/basic_types.c).

``` c
#include <stdio.h>

int main(void) {
    printf("%d\n",sizeof(char));
    printf("%d\n",sizeof(short));
    printf("%d\n",sizeof(int));
    printf("%d\n",sizeof(unsigned int));
    printf("%d\n",sizeof(long));

    printf("%d\n",sizeof(float));
    printf("%d\n",sizeof(double));

    return 0;
}
```

* There are only two primary interpretations of data in C: *integers* and
  floating-point* values.

* The standard `int` is 4 bytes (32 bits) on most modern machines and devices.
  We can access the value of the maximum integer by the `INT_MAX` constant
  defined in `limits.h`.

  * This value turns out to be `2^(32-1) - 1` which corresponds to the bit
    pattern of all `1`s except for a `0` in the most-significant digit.

  * This representation of integers is called
    (twos-complement)[http://en.wikipedia.org/wiki/Two's_complement] which makes
    implementation of basic numerical operations over these numbers easy.

  * As a result, `1 + INT_MAX` produces the bit pattern `10000000 ... 0`.
    Interpreting this in twos-complement results in the *most-negative* integer
    possible.  This is an example of *arithmetic overflow*.

  * If we know we do not need negative integer values, we can tell C to
    *interpret* the bits not in two's complement but as a standard binary number
    thus reclaiming the sign bit as an additional digit) by using the `unsigned`
    modifier.  Note that the size of the integer type does not change with
    `unsigned`, only the *interpretation* of the bit pattern changes!  Note: 
    `unsigned` can be used to modify any integer data type (e.g. `unsigned char`).

* `long` and `short` are modifiers on the primitive types to change sizes but
   not their interpretation.

* `char` is defined to be the smallest addressable chunk of memory on the
  underlying hardware, i.e., 1 byte.  This comes from the fact that we represent
  individual characters in C using the
  [ASCII](http://en.wikipedia.org/wiki/Ascii) encoding which assigns the values
  0-255 to different characters in the English alphabet along with other
  symbols.

  * Because `char` is a single byte, you frequently see `char` used to represent
    raw byte arrays, e.g., `char buf [100]` declares an array of size 100 bytes
    on the stack.

* The floating point numbers are represented using the [IEEE standard for
  floating-point arithmetic](http://en.wikipedia.org/wiki/IEEE_floating_point)
  which defines how floats are represented with bit strings as well as
  requirements on how operations over those floats should behave.

* As you may have noticed, there is no similar type to Java's `boolean` in the
  previous code sample.  C does not explicitly provide a boolean type, as shown 
  in the following example ([bool.c](bool.c)):

* Main takeaways from this example:
  * Basic data-types: ints and floats and chars
  * unsigned vs. signed and integer overflow
  * char is a byte
  * No boolean in C

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

* Main takeaways from this example:
  * No boolean data type in C
  * bool types and true/false defined in stdbool.h
  * == 0 --> false and != 0 --> true
  * Mixing up == and = is bad

* Like most languages, C also provides arrays.  In C, arrays can be either 
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
    can declare locals in the same places as you would in Java.

* Main takeaways from this example:
  * C array syntax
  * Stack allocation
  * Standards compliant code

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

* As a matter of pragmatics, this bare `struct` definition is rarely what we
  want.  The reason for this is that whenever we want to use this `struct`,
  e.g., a local variable, we must qualify `point` with the `struct` keyword:
  `struct point p`.  This is because the `struct` definition doesn't define a
  type proper but a `struct`.

* Main takeaway from this example:
  * Struct syntax
  * Not object-oriented - No methods

* To define `point` as a type that we can use without qualification, we use
  `typedef` to create an alias for `struct point`.  In general, `typedef`s have
  the following form:

``` c
typedef int error_code;
```

* This example `typedef` defines `error_code` as an alias for `int`.  Therefore
  `error_code` can be used where ever we expect an `int`.  This is useful as a
  point of documentation to have an `error_code` type that is really an `int`.

* We also use `typedef` to bring a `struct` into the type world.  For example,
  in [point.h](src/point.h) we combine `typedef` and `struct` as follows:

``` c
typedef struct point {
    int x;
    int y;
} point;
```

* While it looks redundant, this has the effect of making `point` an alias for
  `struct point` which allows us to use `point` as a type throughout our code.

The C Mental Model of Computation
---------------------------------

* Our C mental model of computation consists of a *stack* and *heap* in memory.
  The stack contains a record of the function calls currently active as well as
  the values of each function's arguments and local variables.  The heap
  contains values that we have explictly allocated with the `malloc` function
  which we will we describe shortly.

* For now, let's consider a simple example to see how this model works.

``` C
int f(int x, int y) {
    x = x * 2;
    y = x + y;
    return x;
}

int main(void) {
    int x = 7;
    int y = 42;
    y = f(x, y);
    return 0;
}
```

* Initially, the stack and heap are empty as shown in this *memory diagram*:

```
Stack                       Heap
-----                       -----
```

* For now, we will not use the heap in this example, so we will elide it from
  future diagrams.

* We start execution on the first line of `main`.  Whenever a function is
  called, we push a new *stack frame* onto the stack that contains its arguments
  and local variables.  `main` is the first function called, and so we push on a
  stack frame for it as well as its two local variables, `x` and `y`:

```
  Stack
  ------
   main
x [    ]
y [    ]
```

* Each local variable gets its own, named slot.  If there were arguments, they
  would also get their own slots as well.  Next, we evaluate each line of `main`
  in turn.  The first two lines are simple declarations and initializations of `x`
  and `y`.  The slots on the stack get the values assigned to them.

```
  Stack
  ------
   main
x [ 7  ]
y [ 42 ]
```

* Next is an assignment to `y`.  The value to be assigned is the result of the
  function call `f`.  So we evaluate the function call by pushing a new stack
  frame for `f`:

```
  Stack
  ------
   main
x [ 7  ]
y [ 42 ]
     f
x [ 7  ]
y [ 42 ]
```

* `f` has two parameters, also named `x` and `y`.  The effect of the function
  call is that we assign into these two cells *copies* of the values passed by the
  caller of the function.  In this case, those values are `7` and `42` which are
  assigned into `x` and `y`, respectively.  Execution then proceeds through `f`.

* `f` first assigns `x * 2` back into `x`.  We first evaluate the right-hand
  side of the assignment.  Variables evaluate to the values that their
  corresponding slots contain on the stack.  Note that the `x` we refer to is
  `f`'s `x` not `main`'s `x` as `main`'s `x` is not visible to `f`.  So `x * 2`
  evaluates to `7 * 2` which in turn evaluates to `14`.  This value is then
  stored in `x`.

```
  Stack
  ------
   main
x [ 7  ]
y [ 42 ]
     f
x [ 14 ]
y [ 42 ]
```

* Next we perform the assignment into `y`.  `x + y` evaluates to `14 + 42` which
  in turn evaluates to `56` which is put back into `y`'s slot.

```
  Stack
  ------
   main
x [ 7  ]
y [ 42 ]
     f
x [ 14 ]
y [ 56 ]
```

* Finally, we return `x`.  The effect of the `return` statement is to *pop* or
remove the current stack frame.  The value that is returned becomes the result
of the function call.  In this case, the value contained in `x`, `14` becomes
the return value.  Execution returns to `main`, and we complete the assignment
of `14` into `y`.

```
  Stack
  ------
   main
x [ 7  ]
y [ 14 ]
```

* We will use this mental model of computation throughout these notes to help
  explain how the C language functions.  Remember that if you ever encounter
  strange and confusing behavior in your code, you should fall back on this
  mental model to try to make sense of the situation.