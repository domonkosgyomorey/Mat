#define MAT_IMPLEMENTATION  
#include "mat.h"

float addOne(float val){
    return val+1;
}

int main(){
    Mat m = mat_alloc(2, 2);
    mat_put(m, (float[]){1, 0, 0, 1}, 4);
    mat_print(m);
    Mat m2 = mat_alloc(2, 3);
    mat_put(m2, (float[]){1, 0, 0, 0, 1, 0}, 6);
    mat_print(m2);
    Mat ans = mat_mul(m, m2);
    mat_print(ans);
    Mat add = mat_add(ans, m2);
    mat_print(add);
    mat_serialize(ans, "ans.mat");
    Mat des = mat_deserialize("ans.mat");
    mat_print(des);
    mat_map(des, addOne);
    mat_print(des);
    return 0;
}
