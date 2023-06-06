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

#define ll long long int

#define MAT_AT(M, R, C) M.data[(R)*M.col+(C)]
#define MAT_MAGIC 0x4d4154

typedef struct Mat
{
    ll row, col;
    float *data;
} Mat;

Mat mat_alloc(ll row, ll col);
void mat_put(Mat mat, float* data, ll len);
void mat_print(Mat mat);
Mat mat_mul(Mat a, Mat b);
Mat mat_add(Mat a, Mat b);
Mat mat_deserialize(const char* filename);
void mat_serialize(Mat mat, const char* filename);
Mat mat_deserialize_ex(void (*read_f)(float*, ll), void (*read_st)(ll*, ll));
void mat_serialize_ex(Mat mat, void (*write_f)(float*, ll), void (*write_st)(ll*, ll));
void mat_map(Mat mat, float (*map)(float));

#ifdef MAT_IMPL

Mat mat_alloc(ll row, ll col){
    float *data = (float*)MAT_CALLOC(row*col, sizeof(float));
    MAT_ASSERT(data!=NULL && "Cannot allocate memory for the matrix");           
    return (Mat){row, col, data};
}

void mat_put(Mat mat, float* data, ll len){
    MAT_ASSERT(len==mat.col*mat.row);
    for(ll i = 0; i < len; i++){
        mat.data[i] = data[i];
    }
}

void mat_print(Mat mat){
    MAT_PRINT("Mat (%zux%zu):\n", mat.row, mat.col);    
    for(ll i = 0; i < mat.row; i++){
        for(ll j = 0; j < mat.col; j++){
            MAT_PRINT("%.04f ", MAT_AT(mat, i, j));
        }
        MAT_PRINT("\n");
    }
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
    ll magic[1];
    MAT_FREAD(magic, sizeof(ll), 1, file);
    ll buff[2];
    MAT_ASSERT(MAT_FREAD(buff, sizeof(ll), 2, file)==2);
    Mat mat = mat_alloc(buff[0], buff[1]);
    MAT_ASSERT(MAT_FREAD(mat.data, sizeof(float), mat.row*mat.col, file)==mat.row*mat.col);
    MAT_FCLOSE(file);
    return mat;
}

void mat_serialize(Mat mat, const char* filename){
    FILE* file = MAT_FOPEN(filename, "wb");
    ll magic[1] = {MAT_MAGIC};
    MAT_FWRITE(magic, sizeof(ll), 1, file);
    ll buff[2] = {mat.row, mat.col};
    MAT_FWRITE(buff, sizeof(ll), 2, file);
    MAT_FWRITE(mat.data, sizeof(float), mat.row*mat.col, file);
    MAT_FCLOSE(file);
}

Mat mat_deserialize_ex(void (*read_f)(float*, ll), void (*read_st)(ll*, ll)){
    ll magic[1];
    read_st(magic, sizeof(ll));
    ll buff[2];
    read_st(buff, 2);
    Mat mat = mat_alloc(buff[0], buff[1]);
    read_f(mat.data, mat.row*mat.col);
    return mat;
}

void mat_serialize_ex(Mat mat, void (*write_f)(float*, ll), void (*write_st)(ll*, ll)){
    ll magic[1] = {MAT_MAGIC};
    write_st(magic, sizeof(ll));
    ll buff[2] = {mat.row, mat.col};
    write_st(buff, 2);
    write_f(mat.data, mat.row*mat.col);
}

void mat_map(Mat mat, float (*map)(float)){
    for(ll i = 0; i < mat.col*mat.row; i++){
        mat.data[i] = map(mat.data[i]);
    }
}

#endif // MAT_IMPL

#endif // MAT_H
