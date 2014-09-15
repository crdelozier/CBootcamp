The C Compilation Model
=======================

* The first major depature from a high-level programming language to C is the
  compilation model.

  * This may seem like a boring topic, but it is important because many of the
    problems a new C programmer runs into is not necessarily with the language
    but with the building and including libraries.  To debug these issues, even
    in the context of support tools such as build systems and IDEs, you
    need to understand the C compilation model.

Separate Compilation
--------------------

* So far, we've compiled programs on the Unix command-line as follows, e.g.,
  with [hello.c](src/hello.c)

```
$ gcc test.c -o test
$ la
test  test.c
```

* This command compiles the `test.c` file and creates a program called `test`.
  We can think of the current pipeline as follows:

```
**********  gcc   ********
* test.c * -----> * test *
**********        ********
  C src           Program
```

* However, gcc is doing more behind the scenes which we can reveal with the `-c`
  flag.

```
$ gcc test.c -c
$ ls
test.c  test.o
```

* By specifying the `-c` flag, we tell gcc to compile each source file to an
  *object file* rather than a final program.  An object file contains compiled
  code (i.e., machine code) coupled with *holes* that we will explain shortly.

* From here, we can compile all the object files (here just `hello.c`) into the
  final executable by invoking `gcc` again.

```
$ gcc test.o -o test
$ ls
test  test.c  test.o

* Now the compilation pipeline looks like this:

```
**********  gcc -c   **********   gcc   ********
* test.c * --------> * test.o * ------> * test *
**********           **********         ********
  C src               Obj. file         Program
        (Compilation)          (Linking)
```

* We'll call the process of going from a C source file to its corresponding
  object file *compilation*.  The final step of taking object files into a final
  program is called *linking*.  During linking, we analyzes the holes in the
  object files and patch them with code from object files.

* This is less interesting for programs consisting of a single file.  It is more
  interesting when we have multiple files contributing to a single program.  For
  example, consider [multi_cu1.c](src/multi_cu1.c),
  [multi_cu2.c](src/multi_cu2.c), and [multi_cu.h](src/multi_cu.h).

``` c
///// multi_cu1.c /////
#include "multi_cu.h"

#define MY_CONSTANT 42

int main(void) {
    print_num(MY_CONSTANT);
    return 0;
}

///// multi_cu2.c /////
#include "multi_cu.h"
#include <stdio.h>

void print_num(int n) {
    printf(">> %d <<\n", n);
}

///// multi_cu.h /////
#ifndef _MULTI_CU_H
#define _MULTI_CU_H

void print_num(int n);

#endif // _MULTI_CU_H
```

* To compile the entire program, we compile each of the .c files separately into
  object files and then combine those two object files during linking into a
  final executable.

```
$ gcc -c multi_cu1.c multi_cu2.c
$ ls
multi_cu1.c  multi_cu1.o  multi_cu2.c  multi_cu2.o  multi_cu2.h
$ gcc multi_cu1.o multi_cu2.o -o prog
$ ls
multi_cu1.c  multi_cu1.o  multi_cu2.c  multi_cu2.o  multi_cu2.h  prog
```

* The architecture of our simple program is as follows:

  * `multi_cu.h` is a *header file* denoted with the `.h` extension.  In it, we
    define the *prototype* for the function `print_num`.  A prototype states the
    function signature (the types of its arguments as well as its return type)
    without its definition.  This file is read in and shared between
    `multi_cu1.c` and `multi_cu2.c` via the `#include` pre-processor directive
    which includes a copy of the contents of `multi_cu.h` in the place of the
    directive.  For now you can ignore the other pre-processor directives (lines
    starting with `#`) in the file.

  * In `multi_cu1.c` we define the `main` function which in uses the `print_num`
    function prototyped in `multi_cu.h` and defined in `multi_cu1.c`.  Note that
    `multi_cu1.c` only knows about the signature of `print_num` through
    `multi_cu.h`.  During the compilation phase, it knows nothing about
    `multi_cu2.c`.  The `#define` pre-processor directive defines a constant.
    In this case, the constant called `MY_CONSTANT` with value 42.

  * In `multi_cu2.c` we finally define the `print_num`.

* The compilation pipeline of our program looks as follows:

```
*************** gcc -c ***************
* multi_cu1.c * -----> * multi_cu1.o *
***************        ***************
       ^                             |
       | #include                    |
***************                      |    ********
* multi_cu.h  *                  gcc ---> * prog *
***************                      |    ********
       | #include                    |
       V                             |
*************** gcc -c ***************
* multi_cu1.c * -----> * multi_cu2.o *
***************        ***************
           (Compilation)          (Linking)
```

* Note that `multi_cu1.c` and `multi_cu2.c` are *compiled separately and produce
  two separate object files.
  * The file `multi_cu1.o` contains machine code with a hole awaiting the
    definition of `print_num`.
  * The file `multi_cu2.o` contains the definition of `multi_cu2.o`.

* The process of linking plugs the hole for `print_num` in `multi_cu1.o` with
  the definition from `multi_cu2.o`.  The final machine code is what goes into
  the final `prog` executable at the end.

* If we forgot to include `multi_cu2.o` during the linking step, then we would
  get a linker error complaining that no definition for `print_num` can be
  found.

* Note that `#include`ing the header file `multi_cu.h` in `multi_cu1.c` does not
  tell the compiler where to find the implementation of `print_num`!  It merely
  tells `multi_cu.c` the type information necessary to create the hole in the
  object file.  We could've duplicated the prototype in both `multi_cu1.c` and
  `multi_cu2.c` and gotten the same effect.  However, the header file allows us
  to share the prototype between the two files without duplication of code.

* A .c file together with all the files it `#include`es is called a
  **compilation unit**.   In C and C++, compilation units are independent units
  of compilation that produce a corresponding object file.

* The big win here is that we gain **separate compilation**.  If we modify only
  one of the compilation units, we can re-compile only that unit to get a new,
  updated object file.  We can then link this against the old object file to get
  a new program.  We frequently want to make small changes to a single file and
  then quickly recompile to check the changes.  Separate compilation supports
  this model of development by making incremental changes quick to compile.