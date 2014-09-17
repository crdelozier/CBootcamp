Debugging
==========

gdb
------------

* gdb is a command-line debugging tool for C and C++ programs on Unix 
  systems.  I will give a brief overview of how to use gdb.  For more 
  information, you can look at the the gdb website here: 
  http://www.gnu.org/software/gdb/.

* Demonstrations for gdb will be done live.  I will add some notes 
  after.  The following topics will be covered:
  * Compiling programs with `-g` for debugging support
  * Running programs with gdb
  * Generating backtraces
  * Examining program state
  * Setting breakpoints (and conditions)
  * Stepping through code

valgrind
------------

* valgrind is another command-line debugging tool that can be used
  on Unix systems (on which it is installed).  It is available on 
  eniac.

* Unlike gdb, valgrind is useful for finding memory safety errors
  that do not trigger a segmentation fault.  gdb will only stop at 
  a user-defined breakpoint or when a signal is caught (such as a 
  segmentation fault).  valgrind will report memory safety issues
  regardless of if the memory safety error crashes the program or 
  not.

* valgrind will catch most memory safety errors.  There is a small
  chance that it will miss them due to the algorithm that it uses, 
  but this is unlikely in practice.  However, valgrind will run 
  your program at roughly 100x overhead due to its use of dynamic
  binary instrumentation.

* Let's look at a few examples from the section on explicit memory 
  management to see how valgrind diagnoses memory safety issues.

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

```
==12165== Invalid write of size 4
==12165==    at 0x4005E9: main (buffer_overflow.c:8)
==12165==  Address 0x51e0068 is 0 bytes after a block of size 40 alloc'd
==12165==    at 0x4C2C27B: malloc (in /usr/lib64/valgrind/vgpreload_memcheck-amd64-linux.so)
==12165==    by 0x4005BD: main (buffer_overflow.c:4)
```

* valgrind tells us that an invalid write of size 4 occurs at line 8 of the 
  code sample.  The line in question is `a[c] = c;`.  valgrind has correctly
  identified that a buffer overflow has occurred at this line.

* valgrind tells us that the write is `0 bytes after a block of size 40 alloc'd`.  
  This means that the write is at the byte directly after an allocation of size 
  40, which is equal to `10 * sizeof(int)`.

* valgrind also informs us that the allocation was initially created at line 4 
  of the code sample, which is where the code calls `malloc()`.

* Next, let's look at the use after free example.

```
#include <stdlib.h>

int main(void){
    int *p = (int*)malloc(sizeof(int));
    free(p);

    *p = 5;

    return 0;
}
```

```
==12217== Invalid write of size 4
==12217==    at 0x400622: main (use_after_free.c:7)
==12217==  Address 0x51e0040 is 0 bytes inside a block of size 4 free'd
==12217==    at 0x4C2AF6C: free (in /usr/lib64/valgrind/vgpreload_memcheck-amd64-linux.so)
==12217==    by 0x40061D: main (use_after_free.c:5)
```

* As you can see, valgrind again correctly identifies that a use-after-free error
  has occurred.  It gives us the message that the address is `0 bytes inside a 
  block of size 4 free'd`.

* Instead of indicating where the `malloc()` call for this block of memory occurred, 
  valgrind tells us that the block of memory was freed at line 5.

* valgrind also tells us that the offending use-after-free occurred at line 7 of the 
  sample code.

* Finally, let's look at how valgrind handles uninitialized memory and null pointer errors.

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

* For this example, valgrind produces 2 distinct error messages.

```
==12243== Use of uninitialised value of size 8
==12243==    at 0x40056C: main (null_pointers.c:7)
```

* This error message indicates that the pointer `p1` has not been properly initialized.
  From the code, we can see that `p1` was never assigned a value.  valgrind correctly 
  identifies this issue and points us to the line of code at which the offending
  access occurred.  In this case, valgrind does not tell us where the pointer was
  declared.

```
==12310== Invalid write of size 4
==12310==    at 0x400576: main (null_pointers.c:8)
==12310==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

* valgrind also produces an error message for the null pointer error.  valgrind informs
  us that there was an invalid write of size 4 (the size of an int on this system).
  valgrind also tells us that the address `0x0 is not stack'd, malloc'd or (recently)
  free'd`.  The address `0x0` given to us by valgrind informs us that this error 
  is a null pointer error.