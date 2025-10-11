#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct {
    double* data;
    size_t rows;
    size_t cols;
} matrix;

#endif

// memory management
matrix* cgemm_mallocMat(size_t rows, size_t cols);
void cgemm_freeMat(matrix* mat);

// data management
void cgemm_fillMat(matrix* mat, const double* data);

// data visualization
void cgemm_printMat(matrix* mat);

// routines
void cgemm_gemm(const double* alpha, matrix* A, matrix* B, const double* beta, matrix* C, matrix* D);