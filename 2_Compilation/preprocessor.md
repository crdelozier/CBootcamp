The C Preprocessor
==================

* The `C preprocessor` is a small language built on top of C for the purposes of
  transforming and generating source code.

  * During compilation, the preprocessor runs first over your source file
    transforming it based off of the *preprocessor directives* that you specify.

  * To see the result of running the preprocessor on your source, you can give
    the `-E` flag instead of the `-o` or `-c` flags to `gcc`.

#include
--------

* `#include` is our first example of a preprocessor directive.  It tells the
  preprocessor to include a copy of the contents of the specified file in place
  of the directive, i.e., it is a *textual substitution* of the directive for a
  file.

  * When you specify the file in angle brackets, e.g., `#include <stdio.h>`, you
    tell the preproecssor to search for the file in the set of *system
    directories*, e.g., `\usr\include` on a Unix-type machine.

  * When you specify the file in quotes, e.g., `#include "cu.h"`, you tell the
    preprocessor to search for the file in the current directory.

  * In general, you can specify any *relative path* to `#include`, e.g.,
    `#include "include/foo.h"` tells the pre-processor to find `foo.h` inside of
    the `include` directory in the current directory.

#define
-------

* Another preprocessor directive is `#define` which defines a substitution of
  one chunk of text for another also known as a *macro*.  In
  [multi_cu1.c](src/multi_cu1.c) we have the following use of `#define`:

``` c
#define MY_CONSTANT 42
```

* This directive tells the preprocesor from this point on in the program, if we
  see the text `MY_CONSTANT`, replace it with `42`.

* We can define macros that take arguments, e.g., a `MAX` macro that textually
expands to an expression that computes the max of two values.

``` c
#define MAX(x, y) x > y ? x : y
```

* When we use `MAX`, we provide two pieces of text that will be substituted for
  `x` and `y`.

  * E.g., `MAX(5, 3)` expands to `5 > 3 ? 5 : 3` which is an expression that
    evaluates to 5.

    * This is an example of the *ternary* operator which is equivalent to:

``` c
int result;
if (5 > 3) {
    result = 5;
} else {
    result = 3;
}
```

* However, we have a problem if we do anything fancy with the macro, e.g.,
  `MAX(5, MAX(6, 3))` ought to evaluate to `6`, however the macro expands as
  follows.

``` c
    MAX(5, MAX(6, 3))
|-> MAX(5, 6 > 3 ? 6 : 3)
|-> 5 > 6 > 3 ? 6 : 3 ? 5 : 6 > 3 ? 6 : 3
```

* Because of precedence (`>` binds tighter than `?` and `>`), this expression
  evaluates to 5.

* This is an example of an *unhygenic macro*, one that is easily influenced by
  its surrounding context in unpredictable ways.  To clean up this macro, we can
  use parenthesis to make sure things are evaluated correctly in all possible
  contexts:

``` c
#define MAX(x, y) (((x) > (y)) : (x) ? (y))
```

#ifdef
------

* Finally we can conditional include some text based off the presence of a
  constant introduced with `#define`.  This is useful to toggle between "debug"
  and "release" compilation modes, e.g., in [debug_ex.c](src/debug_ex.c)

``` c
#include <stdio.h>

void spew(char *msg) {
#ifdef _MY_DEBUG
    printf(">>> %s\n", msg);
#endif // _MY_DEBUG
}

int main(void) {
    spew("Here comes the message!");
    printf("Hello World!\n");
    spew("We're about to exit the program...");
    return 0;
}
```

* Here we have a function `spew` that acts as a *logger*.  When we're in debug
  mode, we'd like the logger to print extra information to the console, e.g., to
  trace where we are in the program.  We do not want this extra information
  present when we release the final version of the binary.

* Instead of manually inserting and then removing `printf`s, our strategy is to
  factor out all the debug printing to `spew`.  Inside of `spew` is a `#ifdef`
  that checks for the presence of the `_MY_DEBUG` being defined.  If it is
  defined, then the body of `spew` contains the `printf` call as works as
  expected.  If `_MY_DEBUG` is not defined, then the body of `spew` is empty.

* We have two options to define the `_MY_DEBUG` constant:

  * At the top of the file, we can include `#define _MY_DEBUG` which defines the
    pre-processor constant.  We could also use `#define _MY_DEBUG 0` which says
    that all occurrences of `_MY_DEBUG` should expand to `0`, but this is
    unnecessary because we don't care about the substitution aspect of `#define`;
    here we only care about defining `_MY_DEBUG` itself.

  * To avoid having to edit any files, we can use the `-D` flag of gcc to
    `#define` a constant at the top of every file we compile, e.g., `gcc
    -D_MY_DEBUG` debug_ex.c -o prog` `#define`s `_MY_DEBUG` at the top of
    `debug_ex.c`.  Note that there is no space between `-D` and the name of the
    symbol defined.

Header Guards
-------------

* As a final example of the uses of the preprocessor, we introduce *header
  guards* which ensure that a header file is only textually included once in any
  compilation unit.

  * Because `#include` is just a textual inclusion, it is easy to include
    `#include` multiple times when it is unnecessary or worse yet, have a
    *circular* inclusion graph where two files include each other.

  * To avoid this, we use `#ifndef` which is similar to `#ifdef` but includes
    the text if the symbol is *not* defined in a clever way, e.g.,
    [multi_cu.h](src/multi_cu.h).

``` c
#ifndef _MULTI_CU_H
#define _MULTI_CU_H

void print_num(int n);

#endif // _MULTI_CU_H
```

* The first time `multi_cu.h` is included, the symbol `_MULTI_CU_H` is not
  defined so we include the body of the header file.  This does, among other
  things, define `_MULTI_CU_H`.  Now, if we ever `#include "multi_cu.h"` again,
  `_MULTI_CU_H` will be defined and we will thus skip over the header.

* This pattern, called a *header guard*, is so useful and performed in virtually
  every header file that almost all compilers provide a special *pragma* or
  compiler-specific preprocessor directive that ensures the compiler never reads
  the same header file twice.  This pragma is called `#pragma once` and you can
  feel free to use it in your headers in lieu of the header guard pattern.