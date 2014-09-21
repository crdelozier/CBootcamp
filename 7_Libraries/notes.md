C Standard Libraries
=====================

* C provides a standard library for programmers to use.  These header files
  contain functions to perform common tasks, such as reading from and writing
  to files.

stdlib.h
-----------

* The stdlib.h header contains utility functions for converting strings
  to integer data types, generating random numbers, allocating memory, 
  executing system commands, searching, sorting, and performing some 
  integer arithmetic.

* The first category of functions in stdlib.h are those that convert 
  strings to other data types.  We have already seen one of these functions 
  in a prior example.

* A full list of the functions contained in the stdlib.h header can be found 
  at http://www.cplusplus.com/reference/cstdlib/.

```
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

* The second category of functions found in stdlib.h are those that deal 
  with generating random numbers.  An example is given below of how to
  use the `rand()` and `srand()` functions.

```
#include <stdlib.h>
#include <stdio.h>

int main(void){
    srand(3);
    int r = rand() % 100;
    printf("%d\n",r);
    return 0;
}
```

* We have already covered two of the memory allocation functions found in 
  stdlib.h (`malloc()` and `free()`).  The other two functions are 
  `calloc()`, which allocates zeroed-out memory and `realloc()`, which 
  reallocates memory.

```
void* calloc(size_t num, size_t size);
void* realloc(void *ptr, size_t size);
```

* We should note that `calloc()` has a different form than all of the 
  other allocation functions.  Instead of taking a size in bytes, it 
  asks for the size (in bytes) of each object being allocated and 
  the total number of objects to allocate.
  * `calloc()` uses a different form for its arguments for historical 
    reasons.  The size and number of objects used to be used to align
    the objects in memory.  However, once `malloc()` was introduced
    to the standard library, it was determined that all allocations 
    should be aligned.

* `realloc()` may move the block of memory to a new location.  Any internal
  pointers to the old block of memory must be updated to point to the new block.
  For example, some tree data structures may have pointers to internal nodes.

* stdlib.h also contains the `abort()` and `exit()` functions, which can be 
  used to terminate the program.

* The `system()` function can be used to execute a system call.

```
#include <stdlib.h>

int main(){
  int ret_value = system("mkdir testdir");
  return ret_value;
}
```

* C also provides functions in stdlib.h for sorting and searching arrays.
  Both of these functions require the use of a comparison function, which 
  is provided by the user as a function pointer.

```
void qsort(void *base, size_t num, size_t size, 
           int (*compare)(const void*,const void*));

void* bsearch(const void *key, const void *base, size_t num, size_t size,
              int (*compare)(const void*,const void*));
```

* As you can see from the function definition, the last argument to both 
  of these functions is a comparison function, defined by the user.  In 
  the following example, we show how to define this function and use it.
  [search_sort.c](search_sort.c)

```
#include <stdlib.h>
#include <stdio.h>

#define NUM 50

typedef struct point_t{
    int x;
    int y;
} point;

int compare_points(const void *v1, const void *v2){
    point *p1 = (point*)v1;
    point *p2 = (point*)v2;

    if(p1->x > p2->x && p1->y > p2->y){
        return 1;
    }else if(p1->x < p2->x && p1->y < p2->y){
        return -1;
    }else{
        return 0;
    }
}

int main(){
    point *points = (point*)malloc(NUM * sizeof(point));
    int c = 0;

    points[0].x = 5;
    points[0].y = 7;

    for(c = 1; c < NUM; c++){
        points[c].x = rand() % 100;
        points[c].y = rand() % 100;
    }

    qsort(points,NUM,sizeof(point),compare_points);

    point point_to_find;
    point_to_find.x = 5;
    point_to_find.y = 7;

    point *p1 = (point*)bsearch(&point_to_find,points,NUM,sizeof(point),compare_points);
    if(p1 != NULL){
        printf("Found it!\n");
    }

    point_to_find.x = 1000;
    point_to_find.y = 1000;

    point *p2 = (point*)bsearch(&point_to_find,points,NUM,sizeof(point),compare_points);
    if(p2 != NULL){
        printf("Found it?\n");
    }

    return 0;
}
```

* Finally, the stdlib.h header has a few functions for integer math operations, such as
  absolute value (`abs()`).

stdio.h
-----------

* The stdio.h header contains functions for reading and writing to the console and to 
  files.  For many of these functions, there is a version available with a size argument
  and a version available without a size argument.  The function with the size argument 
  should always be preferred for safety (to avoid buffer overflows).  For example, 
  `sprintf()` is less safe than `snprintf()`.

* We have already used the `printf()` function.  This stdio.h header has similar functions 
  for writing to files (`fprintf()`) and writing to strings (`sprintf()`).

* Let's look at how to read and write to files in C.

```
#include <stdio.h>

int main(){
  FILE *file = fopen("test.txt","w");
  char buf[100];
  int num = 0;

  // Check to see if the file was created or not                                                                                    
  if(file == NULL){
    return 1;
  }

  num = fprintf(file,"Hello!\n");

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  fclose(file);

  file = fopen("test.txt","r");

  if(file == NULL){
    return 1;
  }

  num = fscanf(file,"%s",buf);

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  fclose(file);

  printf("%s\n",buf);

  return 0;
}
```

* In this example, we open a file, write to it, close the file, 
  reopen it for reading, and read the message back into a string.

* After each read or write, we check that there were some number 
  of characters read or written.  This is a limited form of error
  checking, but it's better than nothing.

* We also check to see if `ferror()` has been set.  If it has, 
  we could use `perror()` to print a human readable error message.

* The stdio.h header also contains methods that can write and read
  binary data (i.e. data structures).

```
#include <stdio.h>
#include <stdlib.h>

typedef struct point_t{
  int x;
  int y;
} point;

int main(){
  size_t num;
  point p1;
  point p2;
  FILE *file;

  p1.x = 5;
  p1.y = 7;

  file = fopen("test.bin","wb");

  if(file == NULL || ferror(file) != 0){
    return 1;
  }

  num = fwrite(&p1,sizeof(point),1,file);

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  fclose(file);

  file = fopen("test.bin","rb");

  if(file == NULL || ferror(file) != 0){
    return 1;
  }

  num = fread(&p2,sizeof(point),1,file);

  if(num == 0 || ferror(file) != 0){
    return 1;
  }

  printf("(%d,%d)\n",p2.x,p2.y);

  return 0;
}
```

* Notice that we've opened both files with the `b` flag, designating
  that they're being used for binary reading and writing.

math.h
-----------

* The math.h header contains standard mathematical functions.  You can 
  find a full list of them here: http://www.cplusplus.com/reference/cmath/.

string.h
-----------

* The string.h header contains functions for working with C-strings (arrays of 
  characters).  This header also contains some functions that are generally 
  used as utility functions for memory that does not strictly contain C-strings.

* This is one of the most dangerous (in terms of possible memory safety violations) 
  headers in the C standard library.  Please use caution when using these functions.

* First, we'll cover the memory utility functions provided by the string.h header.  
  These functions are `memcpy()`, `memmove()`, `memcmp()`, and `memset()`.  These 
  functions can be used on C-strings, but they are often used on other types of 
  memory.

* These functions are often highly optimized and may be faster than doing the 
  same process manually in your code (i.e. copying each object from one array 
  to another by iterating over the array).

```
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

int main(){
  int *a = (int*)malloc(SIZE * sizeof(int));
  int *b = (int*)malloc(SIZE * sizeof(int));
  int *c = (int*)malloc(SIZE * sizeof(int));
  int i = 0;

  for(i = 0; i < SIZE; i++){
    a[i] = i;
  }

  memset(b,0,SIZE * sizeof(int));
  memset(c,0,SIZE * sizeof(int));

  memcpy(b,a,SIZE * sizeof(int));
  memmove(c,a,SIZE * sizeof(int));

  if(memcmp(a,b,SIZE * sizeof(int)) == 0){
    printf("A and B are the same!\n");
  }

  if(memcmp(b,c,SIZE * sizeof(int)) == 0){
    printf("B and C are the same!\n");
  }

  return 0;
}
```

* The other functions included in the string.h header are those that are meant
  to perform useful operations on C-strings.

* Like some of the functions in stdio.h, many of the functions in string.h have
  versions that include a size parameter.  You should prefer using these functions 
  to avoid buffer overflow errors.

* The full list of functions included in the string.h header can be found here:
  http://www.cplusplus.com/reference/cstring/

```
#include <string.h>
#include <stdio.h>

int main(){
  char buf[100];
  char *tok;

  strncpy(buf,"Hello world!",13);
  printf("%s\n",buf);

  strncat(&buf[12]," Hello again!",14);
  printf("%s\n",buf);

  if(strncmp(buf,"Hello",5) == 0){
    printf("They match\n");
  }

  printf("String length: %d\n",strlen(buf));
  printf("%s\n",strchr(buf,'!'));
  printf("%s\n",strstr(buf,"world"));

  tok = strtok(buf,"!");
  printf("%s\n",tok);
  tok = strtok(NULL,"!");
  printf("%s\n",tok);

  return 0;
}
```

signal.h
-----------

* The signal.h header contains functions for sending and receiving system signals.
  This header contains only two functions: `signal()` and `raise()`.

```
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int param){
  printf("Null pointer exception!\n");
}

int main(){
  void (*previous_handler)(int);
  int *p = NULL;

  previous_handler = signal(SIGSEGV,handler);

  raise(SIGSEGV);

  return 0;
}
```

* In this example, we handle the `SIGSEGV` signal, which occurs when a null pointer
  is dereferenced.  The `signal()` function registers our handler function to be 
  called when a `SIGSEGV` signal is raised in the system.  We then manually call 
  `raise()` to demonstrate this behavior.

* Note: Please do not handle `SIGSEGV` in real code.  Just let the program crash.