#include <stdio.h>

#ifdef _DEBUG
#define PRINT(x) printf(x);
#else
#define PRINT(x)
#endif

int main(){
  PRINT("Hello world %d!\n",5)
  return 0;
}
