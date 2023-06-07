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

## Example code
```C
#define MAT_IMPL
#include "mat.h"

double addOne(double val){
    return val+1;
}

int main(){
    Mat m = mat_alloc(2, 2);
    mat_put(m, (double[]){1, 0, 0, 1}, 4);
    printf("first:\n");
    mat_print(m);

    Mat m2 = mat_alloc(2, 3);
    mat_put(m2, (double[]){1, 0, 0, 0, 1, 0}, 6);
    printf("Second:\n");
    mat_print(m2);
    
    Mat ans = mat_mul(m, m2);
    printf("First*Second=\n");
    mat_print(ans);
    
    Mat add = mat_add(ans, m2);
    printf("Prev+Second=\n");
    mat_print(add);
    
    mat_serialize(add, "ans.mat");
    
    Mat des = mat_deserialize("ans.mat");
    printf("Deserialized:\n");
    mat_print(des);

    mat_map(des, addOne);
    printf("Mapped:\n");
    mat_print(des);

    printf("5x5 identity matrix:\n");
    Mat mat = mat_identity_mat(5);
    mat_print(mat);
    return 0;
}
```

## Compile and run for this example
```console
make
./main
```
