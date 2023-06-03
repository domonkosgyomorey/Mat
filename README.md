# Mat
## Description
A single header matrix library, which can work without any dependency

## How to work with, without any std library ?
You need to walkthought to see which macro you need to define before include this library to use it without any standard library.

BUT, the parameters in your own function must need to equal with the original's parameter !!!

### Example to use this library without printf
You need to define MAT_PRINT before you include the header.
```C
#define MAT_PRINT my_print_fun
#define MAT_IMPLEMENTATION
#include<mat.h>
```
## Usage for this example
```console
make
./main
```
