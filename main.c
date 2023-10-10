#define MAT_IMPL
#include "mat.h"

double addOne(double val){
    return val+1;
}

int main(){
    Mat *m = mat_alloc(2, 2);
    mat_put(m, (double[]){1, 0, 0, 1}, 4);
    printf("first:\n");
    mat_print(m);

    printf("\n");
    Mat *m2 = mat_alloc(2, 3);
    mat_put(m2, (double[]){1, 0, 0, 0, 1, 0}, 6);
    printf("Second:\n");
    mat_print(m2);
    
    printf("\n");
    Mat *ans = mat_mul(m, m2);
    printf("First*Second=\n");
    mat_print(ans);
    
    printf("\n");
    Mat *add = mat_add(ans, m2);
    printf("Prev+Second=\n");
    mat_print(add);
    
    mat_serialize(add, "ans.mat");
    
    printf("\n");
    Mat *des = mat_deserialize("ans.mat");
    printf("Deserialized:\n");
    mat_print(des);

    printf("\n");
    mat_map(des, addOne);
    printf("Mapped:\n");
    mat_print(des);

    printf("\n");
    printf("5x5 identity matrix:\n");
    Mat *mat = mat_identity_mat(5);
    mat_print(mat);

    printf("\n");
    mat_put_col(mat, (double[]){1, 2, 3, 4, 5}, 5, 1);
    printf("Modified 2nd column in the matrix:\n");
    mat_print(mat);
    
    printf("\n");
    printf("Id matrix's sub matrix from (0;1) to (1;2):\n");
    mat_print(mat_get_submat(mat, 0, 1, 2, 2));

    printf("\n");
    printf("Id matrix dimension decreased:\n");
    mat_print(mat_dec_dim(mat, 0, 0));

    printf("\n");
    Mat *identity = mat_identity_mat(5);
    printf("Determinant of id matrix: %lf\n", mat_det(identity));

    mat_print(mat);

    printf("\n");
    printf("The gaussed matrix:\n");
    mat_print(mat_gauss(mat));

    return 0;
}
