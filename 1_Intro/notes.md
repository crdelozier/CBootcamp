The Basics
==========

* We begin with the C programming language!
  + Unlike C++, C is a simpler language with fewer constructs. It is therefore
    a good vehicle to learn the fundamental of systems programming.

* Leverage what you know already (i.e., a C-like language like Java or C# or
  another high-level language like Python).  Let's explore a number of code
  examples to see what transfers and what differences we must keep in mind.

* First example, the canonical [Hello World! (hello.c) program](hello.c).

``` c
#include <stdio.h>

int main(void) {
    printf("Hello World!\n");
    return 0;
}
```

* C is a *procedural* language.  Unlike object-oriented languages like C++ and
  Java C programs are merely a collection of functions.  There are data structures
  (structs), but they only store data and have no associated methods.

* `#include <stdio.h>` includes the *function prototype* or *header* for
  `printf` which prints a string to the console.  Note that `printf` does not
  include a newline character automatically so we must manually enter it.

* The signature for `main` states that `main` takes no arguments (i.e.,
  `void`) and returns an `int`.  The return value corresponds to the program's
  exit code which is used to signal to other programs if the program terminated
  successfully or failed in some way.  0 indicates success, and we will be using
  this exit code for the remainder of the notes.

  + Note that in C using `void` is identical to specifying nothing within
    the parenthesis for *function definitions*.  According to the C
    standard, `void` is required for function prototypes, i.e., forward
    declarations of a function's parameters and return type without its
    corresponding function body.  However, most compilers will accept empty
    parenthesis in either situation without complaint.

* Next, let's jump ahead a bit and examine a program that processes some user 
  input with [read_args_ex.c](read_args_ex.c):

``` c
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s [true|false]", argv[0]);
    } else {
        int val = atoi(argv[1]);
        if (val == 100) {
            printf("That's a good number!\n");
        } else {
            printf("%d is a bad number!\n", val);
        }
    }
    return 0;
}
```

* Here we actually process the arguments passed in from the user (after
  verifying they indeed pass an argument in addition to the name of the
  program).

  * To process the argument we use the `atoi` function (i.e., ascii string
    **to** integer) which is declared in ```stdlib.h``` header which
    contains a variety of essential functions such as the type converters like
    `atoi` and others.

    * Note: C-strings must be null-terminated, meaning that they must end in 
      the character `\0`.  Functions like `atoi` rely on the fact that a 
      C-string is null-terminated by looking for that specific character.

  * The argument `argv` is a two-dimensional array of characters.  If you're 
    not already familiar with two-dimensional arrays from another language
    ,like Java, ignore it for now.  We will cover arrays in the next few
    sections.

  * In this example, we use a format string as the argument to `printf`.
    This function accepts a string that contains special format placeholders, 
    such as `%d`.  These format placeholds tell the printf function to 
    expect a certain type of data to be printed.  In this case, `%d` tells 
    the function to expect an integer.  This function can be dangerous 
    if the data-types specified in the format string do not match 
    the number or types of the arguments to the function.  The `printf`
    function will blindly attempt to print the arguments as the data-types
    specified in the format string, possibly causing it to perform unsafe
    actions.