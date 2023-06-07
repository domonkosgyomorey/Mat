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
