#include "mat.h"

float addOne(float val){
    return val+1;
}

void write_f(float* data, ll num){
    MAT_PRINT("%p, %zu\n", data, num);
}

void write_st(ll* data, ll num){
    MAT_PRINT("%p, %zu\n", data, num);
}

void read_f(float* buff, ll num){
    for(ll i = 0; i < num; i++){
        buff[i] = i;
    }
}

void read_st(ll* buff, ll num){
    for(ll i = 0; i < num; i++){
        buff[i] = i;
    }
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
    mat_serialize(add, "ans.mat");
    Mat des = mat_deserialize("ans.mat");
    mat_print(des);
    mat_map(des, addOne);
    mat_print(des);
    
    mat_serialize_ex(des, write_f, write_st);
    Mat new = mat_deserialize_ex(read_f, read_st);
    mat_print(new);
    return 0;
}
