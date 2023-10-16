/*!
    @author Gyömörey Domonkos
    @date 2023.10.16

    @link https://www.github.com/domonkosgyomorey/Mat
    @brief A simple Matrix library for common matrix math and capable for embeded system in a unique way
*/

#ifndef MAT_H
#define MAT_H

#ifndef MAT_CALLOC
#include <stdlib.h>
#define MAT_CALLOC calloc
#endif

#ifndef MAT_MALLOC
#include <stdlib.h>
#define MAT_MALLOC malloc
#endif

#ifndef MAT_PRINT
#include <stdio.h>
#define MAT_PRINT printf
#endif

#ifndef MAT_MEMSET
#include <string.h>
#define MAT_MEMSET memset
#endif

#ifndef MAT_ASSERT
#include <assert.h>
#define MAT_ASSERT assert
#endif

#ifndef MAT_FILE_DESC
#include <stdio.h>
#define MAT_FILE_DESC FILE
#endif

#ifndef MAT_FOPEN
#include <stdio.h>
#define MAT_FOPEN fopen
#endif

#ifndef MAT_FREAD
#include <stdio.h>
#define MAT_FREAD fread
#endif

#ifndef MAT_FWRITE
#include <stdio.h>
#define MAT_FWRITE fwrite
#endif

#ifndef MAT_FCLOSE
#include <stdio.h>
#define MAT_FCLOSE fclose
#endif

#ifndef MAT_STRNCMP
#include <math.h>
#define MAT_STRNCMP strncmp
#endif

#define ll long long int
#define MAT_AT(M_PTR, R, C) M_PTR->data[(R)*M_PTR->col + (C)]
#define MAT_MAGIC "MAT"
#define MAT_MAGIC_SIZE sizeof(MAT_MAGIC)
#define MAT_MAGIC_LEN MAT_MAGIC_SIZE / sizeof(char)

int mat_custom_error = 0;

typedef struct Mat
{
    ll row, col;
    double *data;
} Mat;

typedef struct Mat_gauss_tuple
{
    Mat *mat;
    ll rank;
} Mat_gauss_tuple;

/*!
    @brief Allocate a Mat instance with the specific size
    @param row is the rows number of the Matrix
    @param col is the columns number of the Matrix
    @return The allocated Mat reference
*/
Mat *mat_alloc(ll row, ll col);

/*!
    @brief Fill the Mat instance, with flat data
    @param mat The reference of the Mat instance
    @param data An array of data, which will be in the Mat
    @param len The array length which must equal with the Matrix row*column
*/
void mat_put(Mat *mat, const double *data, ll len);

/*!
    @brief Put data or change data in the Mat, in the specific column
    @param mat The reference of the Mat instance
    @param data An array of data, which will be in the Mat
    @param len The length of the data, which must equal with the row of the mat
*/
void mat_put_col(Mat *mat, double *data, ll len, ll col);

/*!
    @brief Copy the eniry matrix content into a new one
*/
Mat *mat_copy(Mat *mat);

/*!
    @brief Print the Matrix onto the stdout
    @param mat The reference of the Mat instance
*/
void mat_print(Mat *mat);

/*!
    @brief Allocate an identity Mat
    @param row Specify the size of the identiry matrix
    @return The reference of the identity Mat
*/
Mat *mat_identity_mat(ll row);

/*!
    @brief Multiply two Matrix
    @param a reference of the left hand matrix
    @param b reference of the right hand matrix (row must equal with the column of the left hand matrix)
    @return An allocated matrix, which is the result, and the shape is left.row x right.col. On error return NULL
*/
Mat *mat_mul(Mat *a, Mat *b);

/*!
    @brief Add two Matrix into a new allocated
    @param a reference of the left hand side matrix
    @param b reference of the right hand side matrix (shape must equal with the left hand side one)
    @return A new allocated matrix which is the result of the operation. On error return NULL
*/
Mat *mat_add(Mat *a, Mat *b);

/*!
    @brief Deserialize a Matrix from a file into an allocated Matrix
    @param filename the file name of the deserializable file
    @return The allocaated matrix, which was deserialize from a file. On error return NULL
*/
Mat *mat_deserialize(const char *filename);

/*!
    @brief Serialize a Matrix into a file
    @param mat the reference of the matrix, which will be serialized
    @param filename the file name where the Matrix will be serialize. On error does not write into the file
*/
void mat_serialize(Mat *mat, const char *filename);

/*!
    @brief Apply an one variable function for each matrix element in a new Matrix
    @param mat reference of the matrix, where the funtion will be applied
    @param map reference of the applyed funtion, example double plus(double x){return x+1;}
    @return An allocated matrix, which contains the result of the operation on the given matrix
*/
Mat *mat_map(Mat *mat, double (*map)(double));

/*!
    @brief Apply the floor function on the specified mat element ( The given mat does not change )
    @param mat reference of the matrix
    @return An allocated matrix where the function was applied
*/
Mat *mat_floor(Mat *mat);

/*!
    @brief Apply the ceil function on the specified mat element ( The given mat does not change )
    @param mat reference of the matrix
    @return An allocated matrix where the function was applied
*/
Mat *mat_ceil(Mat *mat);

/*!
    @brief Apply the abs function on the specified mat element ( The given mat does not change )
    @param mat reference of the matrix
    @return An allocated matrix where the function was applied
*/
Mat *mat_abs(Mat *mat);

/*!
    @brief Apply the neg function on the specified mat element ( The given mat does not change )
    @param mat reference of the matrix
    @return An allocated matrix where the function was applied
*/
Mat *mat_neg(Mat *mat);

/*!
    @brief Get the matrix except that columns and rows which specified in the parameters
    @param mat reference of the matrix
    @param row the row where the row excluding started
    @param col the column where the column excluding started
    @param nrow the range how many rows we need to exclude
    @param ncol the range how many columns we need to exclude
    @return The new allocated sub matrix of the original one
*/
Mat *mat_get_submat(Mat *mat, ll col, ll row, ll nrow, ll ncol);

/*!
    @brief Calculate the determinant of the given matrix
    @param mat reference of the matrix
    @return The determinant. On error return 0
*/
double mat_det(Mat *mat);

/*!
    @brief Get the matrix with one less row, and column
    @param mat reference of the matrix
    @param del_row_i The row index which will be exluded
    @param del_col_i The column index which will be exluded
    @return An allocated sub matrix of the original one. On error return NULL
*/
Mat *mat_dec_dim(Mat *mat, ll del_row_i, ll del_col_i);

/*!
    @brief Get the gauss eliminated matrix
    @param mat reference of the matrix
    @return Gauss eliminated matrix
*/
Mat *mat_gauss(Mat *mat);

/*!
    @brief Get the reducted gauss eliminated matrix
    @param mat reference of the matrix
    @return Reducted gauss eliminated matrix
*/
Mat *mat_r_gauss(Mat *mat);

/*!
    @brief Get how many independent column vector has in the matrix
    @param mat reference of the matrix
    @return how many independent column vector has in the matrix
*/
double mat_rank(Mat *mat);

/*!
    @brief Get the translate version of the matrix
    @param mat reference of the matrix
    @return the translate version of the matrix
*/
Mat *mat_transpose(Mat *mat);

/*!
    @brief Get the inverse of the input matrix
    @param mat reference of the matrix
    @return the inverse of the input matrix
*/
Mat *mat_inverse(Mat *mat);

/*!
    @brief Get the adjungate matrix of the input matrix
    @param mat reference of the matrix
    @return the inverse of the input matrix
*/
Mat *mat_adjungate(Mat *mat);

#ifdef MAT_IMPL

Mat *mat_alloc(ll row, ll col)
{
    double *data = (double *)MAT_CALLOC(row * col, sizeof(double));
    mat_custom_error = 0;
    MAT_ASSERT(data != NULL && "Cannot allocate memory for the matrix");
    if (mat_custom_error)
    {
        return NULL;
    }
    Mat *res = (Mat *)MAT_CALLOC(1, sizeof(Mat));
    res->row = row;
    res->col = col;
    res->data = data;
    return res;
}

void mat_put(Mat *mat, const double *data, ll len)
{
    mat_custom_error = 0;
    MAT_ASSERT(len == mat->col * mat->row);
    if (mat_custom_error)
    {
        return;
    }
    for (ll i = 0; i < len; i++)
    {
        mat->data[i] = data[i];
    }
}

void mat_put_col(Mat *mat, double *data, ll len, ll col)
{
    mat_custom_error = 0;
    MAT_ASSERT(mat->row == len && mat->col > col && "The matrix size not enough");
    if (mat_custom_error)
    {
        return;
    }
    for (ll i = 0; i < len; i++)
    {
        MAT_AT(mat, i, col) = data[i];
    }
}

Mat *mat_copy(Mat *mat)
{
    Mat *res = mat_alloc(mat->row, mat->col);
    for (ll i = 0; i < mat->col * mat->row; ++i)
    {
        res->data[i] = mat->data[i];
    }
    return res;
}

void mat_print(Mat *mat)
{
    for (ll i = 0; i < mat->row; i++)
    {
        for (ll j = 0; j < mat->col; j++)
        {
            MAT_PRINT("%.04f ", MAT_AT(mat, i, j));
        }
        MAT_PRINT("\n");
    }
}

Mat *mat_identity_mat(ll row)
{
    Mat *mat = mat_alloc(row, row);
    for (ll i = 0; i < row; i++)
    {
        for (ll j = 0; j < row; j++)
        {
            MAT_AT(mat, i, j) = (i == j);
        }
    }
    return mat;
}

Mat *mat_mul(Mat *a, Mat *b)
{
    mat_custom_error = 0;
    MAT_ASSERT(a->col == b->row && "Matrix multiplication rule error");
    if (mat_custom_error)
    {
        return NULL;
    }
    Mat *dest = mat_alloc(a->row, b->col);
    for (ll i = 0; i < b->col; i++)
    {
        for (ll j = 0; j < a->row; j++)
        {
            for (ll k = 0; k < a->col; k++)
            {
                MAT_AT(dest, j, i) += MAT_AT(a, j, k) * MAT_AT(b, k, i);
            }
        }
    }
    return dest;
}

Mat *mat_add(Mat *a, Mat *b)
{
    mat_custom_error = 0;
    MAT_ASSERT(a->row == b->row && a->col == b->col && "The first and the second shape must be equal");
    if (mat_custom_error)
    {
        return NULL;
    }

    Mat *dest = mat_alloc(a->row, a->col);
    for (ll j = 0; j < a->row; j++)
    {
        for (ll k = 0; k < a->col; k++)
        {
            MAT_AT(dest, j, k) = MAT_AT(a, j, k) + MAT_AT(b, j, k);
        }
    }
    return dest;
}

Mat *mat_deserialize(const char *filename)
{
    FILE *file = MAT_FOPEN(filename, "rb");
    char magic[MAT_MAGIC_LEN] = {0};
    MAT_FREAD(magic, sizeof(char), MAT_MAGIC_LEN, file);
    mat_custom_error = 0;
    MAT_ASSERT(MAT_STRNCMP(magic, MAT_MAGIC, MAT_MAGIC_LEN) == 0 && "Incompatible file type");
    if (mat_custom_error)
    {
        return NULL;
    }
    ll buff[2];
    MAT_FREAD(buff, sizeof(ll), 2, file);
    mat_custom_error = 0;
    MAT_ASSERT(buff[0] > 0 && buff[1] > 0 && "Cannot create matrix with row<=0 or col<=0");
    if (mat_custom_error)
    {
        return NULL;
    }
    Mat *mat = mat_alloc(buff[0], buff[1]);
    MAT_FREAD(mat->data, sizeof(double), mat->row * mat->col, file);
    MAT_FCLOSE(file);
    return mat;
}

void mat_serialize(Mat *mat, const char *filename)
{
    FILE *file = MAT_FOPEN(filename, "wb");
    char *magic = MAT_MAGIC;
    ll written = MAT_FWRITE(magic, sizeof(char), MAT_MAGIC_LEN, file);
    mat_custom_error = 0;
    MAT_ASSERT(written == MAT_MAGIC_LEN && "Failed to write into file");
    if (mat_custom_error)
    {
        return;
    }
    ll buff[2] = {mat->row, mat->col};
    written = MAT_FWRITE(buff, sizeof(ll), 2, file);
    mat_custom_error = 0;
    MAT_ASSERT(written == 2 && "Failed to write into file");
    if (mat_custom_error)
    {
        return;
    }
    written = MAT_FWRITE(mat->data, sizeof(double), mat->row * mat->col, file);
    mat_custom_error = 0;
    MAT_ASSERT(written == mat->row * mat->col && "Failed to write into file");
    if (mat_custom_error)
    {
        return;
    }
    MAT_FCLOSE(file);
}

Mat *mat_map(Mat *mat, double (*map)(double))
{
    Mat *res = mat_alloc(mat->row, mat->col);
    for (ll i = 0; i < mat->col * mat->row; i++)
    {
        res->data[i] = map(mat->data[i]);
    }
    return res;
}

Mat *mat_floor(Mat *mat)
{
    Mat *res = mat_copy(mat);
    mat_map(res, floor);
    return res;
}

Mat *mat_ceil(Mat *mat)
{
    Mat *res = mat_copy(mat);
    mat_map(res, ceil);
    return res;
}

Mat *mat_abs(Mat *mat)
{
    Mat *res = mat_copy(mat);
    mat_map(res, fabs);
    return res;
}

double mat_util_neg(double x)
{
    return -x;
}

Mat *mat_neg(Mat *mat)
{
    Mat *res = mat_copy(mat);
    mat_map(res, mat_util_neg);
    return res;
}

Mat *mat_get_submat(Mat *mat, ll row, ll col, ll nrow, ll ncol)
{
    mat_custom_error = 0;
    MAT_ASSERT(nrow + row < mat->row && ncol + col < mat->col && "The parameters indexing out");
    if (mat_custom_error)
    {
        return NULL;
    }
    Mat *nmat = mat_alloc(nrow, ncol);
    ll idx = 0;
    for (ll i = 0; i < nrow; i++)
    {
        for (ll j = 0; j < ncol; j++)
        {
            nmat->data[idx++] = MAT_AT(mat, row + i, col + j);
        }
    }
    return nmat;
}

Mat *mat_dec_dim(Mat *mat, ll del_row_i, ll del_col_i)
{
    mat_custom_error = 0;
    MAT_ASSERT(mat->row > 1 && mat->col > 1 && del_row_i < mat->row && del_col_i < mat->col && "Cannot decrease dimension, because the current dim less than 2");
    if (mat_custom_error)
    {
        return NULL;
    }
    Mat *nmat = mat_alloc(mat->row - 1, mat->col - 1);
    ll idx = 0;
    for (ll i = 0; i < mat->row; i++)
    {
        for (ll j = 0; j < mat->col; j++)
        {
            if (i != del_row_i && j != del_col_i)
            {
                nmat->data[idx++] = MAT_AT(mat, i, j);
            }
        }
    }
    return nmat;
}

double mat_det(Mat *mat)
{
    mat_custom_error = 0;
    MAT_ASSERT(mat->row == mat->col && "The shape of Matrix must be square");
    if (mat_custom_error)
    {
        return 0;
    }
    if (mat->row == 2)
    {
        return mat->data[0] * mat->data[3] - (mat->data[1] * mat->data[2]);
    }
    double det = 0;
    for (ll i = 0; i < mat->col; i++)
    {
        det += MAT_AT(mat, 0, i) * mat_det(mat_dec_dim(mat, 0, i)) * (i % 2 == 0 ? 1 : -1);
    }
    return det;
}

Mat_gauss_tuple mat_util_gauss(Mat *mat)
{
    Mat *res = mat_copy(mat);
    ll max_rank = res->col;
    unsigned char was_row[res->row];
    for (ll i = 0; i < res->col; i++)
    {
        ll first_col = -1;
        ll j = -1;
        while (j < res->row)
        {
            j++;
            if (first_col == -1 && was_row[i] != 1 && MAT_AT(res, j, i) != 0)
            {
                first_col = i;
                was_row[i] = 1;
                for (ll k = res->col - 1; k > i - 1; k--)
                {
                    res->data[first_col * res->col + k] /= res->data[first_col * res->col + i];
                }
                j = -1;
                continue;
            }
            if (first_col != -1 && j != first_col)
            {
                if (was_row[j] != 1)
                {
                    for (ll k = res->col - 1; k > -1; k--)
                    {
                        MAT_AT(res, j, k) -= MAT_AT(res, j, i) * MAT_AT(res, first_col, k);
                    }
                }
            }
        }
        if (first_col == -1)
        {
            max_rank -= 1;
        }
    }
    return (Mat_gauss_tuple){.mat = res, .rank = max_rank};
}

Mat *mat_gauss(Mat *mat)
{
    return mat_util_gauss(mat).mat;
}

double mat_rank(Mat *mat)
{
    return mat_util_gauss(mat).rank;
}

Mat *mat_r_gauss(Mat *mat)
{
    Mat *res = mat_gauss(mat);
    for (ll i = mat->row - 2; i > -1; i--)
    {
        double m = MAT_AT(res, i, mat->row - 1);
        for (ll j = 0; j < mat->col; j++)
        {
            MAT_AT(res, i, j) = MAT_AT(res, i, j) - m * MAT_AT(res, i + 1, j);
        }
    }
    return res;
}

Mat *mat_transpose(Mat *mat)
{
    Mat *res = (Mat *)MAT_MALLOC(sizeof(Mat));
    res->row = mat->col;
    res->col = mat->col;
    for (ll i = 0; i < res->row; i++)
    {
        for (ll j = 0; j < res->col; j++)
        {
            MAT_AT(res, i, j) = MAT_AT(mat, j, i);
        }
    }
    return res;
}

Mat *mat_adjungate(Mat *mat)
{
    Mat *res = mat_copy(mat);
    for (ll i = 0; i < res->row; i++)
    {
        for (ll j = 0; j < res->col; j++)
        {
            MAT_AT(res, i, j) = ((i + j) % 2 ? 1 : -1) * mat_det(mat_dec_dim(mat, i, j));
        }
    }
    return res;
}

Mat *mat_div_s(Mat *mat, double y)
{
    Mat *res = mat_copy(mat);
    for (ll i = 0; i < res->row; i++)
    {
        for (ll j = 0; j < res->col; j++)
        {
            MAT_AT(res, i, j) /= y;
        }
    }
    return res;
}

Mat *mat_inverse(Mat *mat)
{
    Mat *res = mat_adjungate(mat);
    return mat_div_s(res, mat_det(res));
}

#endif // MAT_IMPL

#endif // MAT_H
