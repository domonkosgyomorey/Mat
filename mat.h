#ifndef MAT_H
#define MAT_H

#ifndef MAT_CALLOC
#include<stdlib.h>
#define MAT_CALLOC calloc
#endif

#ifndef MAT_PRINT
#include<stdio.h>
#define MAT_PRINT printf
#endif

#ifndef MAT_MEMSET
#include<string.h>
#define MAT_MEMSET memset
#endif

#ifndef MAT_ASSERT
#include<assert.h>
#define MAT_ASSERT assert
#endif

#ifndef MAT_FILE_DESC
#include<stdio.h>
#define MAT_FILE_DESC FILE
#endif

#ifndef MAT_FOPEN
#include<stdio.h>
#define MAT_FOPEN fopen
#endif

#ifndef MAT_FREAD
#include<stdio.h>
#define MAT_FREAD fread
#endif

#ifndef MAT_FWRITE
#include<stdio.h>
#define MAT_FWRITE fwrite
#endif

#ifndef MAT_FCLOSE
#include<stdio.h>
#define MAT_FCLOSE fclose
#endif

#ifndef MAT_STRNCMP
#include <math.h>
#define MAT_STRNCMP strncmp
#endif

#define ll long long int
#define MAT_AT(M, R, C) M.data[(R)*M.col+(C)]
#define MAT_MAGIC "MAT"
#define MAT_MAGIC_SIZE sizeof(MAT_MAGIC)
#define MAT_MAGIC_LEN MAT_MAGIC_SIZE/sizeof(char)

typedef struct Mat
{
    ll row, col;
    double *data;
} Mat;

Mat mat_alloc(ll row, ll col);
void mat_put(Mat mat, double* data, ll len);
void mat_put_col(Mat mat, double* data, ll len, ll col);
void mat_print(Mat mat);
Mat mat_identity_mat(ll row);
Mat mat_mul(Mat a, Mat b);
Mat mat_add(Mat a, Mat b);
Mat mat_deserialize(const char* filename);
void mat_serialize(Mat mat, const char* filename);
void mat_map(Mat mat, double (*map)(double));

#ifdef MAT_IMPL

Mat mat_alloc(ll row, ll col){
    double *data = (double*)MAT_CALLOC(row*col, sizeof(double));
    MAT_ASSERT(data!=NULL && "Cannot allocate memory for the matrix");           
    return (Mat){row, col, data};
}

void mat_put(Mat mat, double* data, ll len){
    MAT_ASSERT(len==mat.col*mat.row);
    for(ll i = 0; i < len; i++){
        mat.data[i] = data[i];
    }
}

void mat_put_col(Mat mat, double* data, ll len, ll col){
    MAT_ASSERT(mat.row==len && mat.col>col && "The matrix size not enough");
    for(ll i = 0; i < len; i++){
        MAT_AT(mat, i, col) = data[i];
    }
}

void mat_print(Mat mat){
    for(ll i = 0; i < mat.row; i++){
        for(ll j = 0; j < mat.col; j++){
            MAT_PRINT("%.04f ", MAT_AT(mat, i, j));
        }
        MAT_PRINT("\n");
    }
}

Mat mat_identity_mat(ll row){
    Mat mat = mat_alloc(row, row);
    for(ll i = 0; i < row; i++){
        for(ll j = 0; j < row; j++){
            MAT_AT(mat, i, j) = (i==j);
        }
    }
    return mat;
}

Mat mat_mul(Mat a, Mat b){
    MAT_ASSERT(a.col==b.row && "Matrix multiplication rule error");
    Mat dest = mat_alloc(a.row, b.col);
    for(ll i = 0; i < b.col; i++){
        for(ll j = 0; j < a.row; j++){
            for(ll k = 0; k < a.col; k++){
                MAT_AT(dest, j, i) += MAT_AT(a, j, k)*MAT_AT(b, k, i);
            }
        }
    }
    return dest;
}

Mat mat_add(Mat a, Mat b){
    MAT_ASSERT(a.row == b.row && a.col == b.col && "The first and the second shape must be equal");
    Mat dest = mat_alloc(a.row, a.col);
    for(ll j = 0; j < a.row; j++){
        for(ll k = 0; k < a.col; k++){
            MAT_AT(dest, j, k) = MAT_AT(a, j, k)+MAT_AT(b, j, k);
        }
    }
    return dest;
}

Mat mat_deserialize(const char* filename){
    FILE* file = MAT_FOPEN(filename, "rb");
    char magic[MAT_MAGIC_LEN] = {0};
    MAT_FREAD(magic, sizeof(char), MAT_MAGIC_LEN, file);
    MAT_ASSERT(MAT_STRNCMP(magic, MAT_MAGIC, MAT_MAGIC_LEN)==0 && "Incompatible file type");
    ll buff[2];
    MAT_FREAD(buff, sizeof(ll), 2, file);
    MAT_ASSERT(buff[0]>0&&buff[1]>0 && "Cannot create matrix with row<=0 or col<=0");
    Mat mat = mat_alloc(buff[0], buff[1]);
    MAT_FREAD(mat.data, sizeof(double), mat.row*mat.col, file);
    MAT_FCLOSE(file);
    return mat;
}

void mat_serialize(Mat mat, const char* filename){
    FILE* file = MAT_FOPEN(filename, "wb");
    char* magic = MAT_MAGIC;
    ll written = MAT_FWRITE(magic, sizeof(char), MAT_MAGIC_LEN, file);
    MAT_ASSERT(written==MAT_MAGIC_LEN && "Failed to write into file");
    ll buff[2] = {mat.row, mat.col};
    written = MAT_FWRITE(buff, sizeof(ll), 2, file);
    MAT_ASSERT(written==2 && "Failed to write into file");
    written = MAT_FWRITE(mat.data, sizeof(double), mat.row*mat.col, file);
    MAT_ASSERT(written==mat.row*mat.col && "Failed to write into file");
    MAT_FCLOSE(file);
}

void mat_map(Mat mat, double (*map)(double)){
    for(ll i = 0; i < mat.col*mat.row; i++){
        mat.data[i] = map(mat.data[i]);
    }
}

#endif // MAT_IMPL

#endif // MAT_H
