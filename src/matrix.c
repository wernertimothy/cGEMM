#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "matrix.h"


matrix* cgemm_mallocMat(size_t rows, size_t cols) {
    matrix* mat = malloc(sizeof(matrix));
    if (!mat) return NULL;
    mat->data = malloc(rows * cols * sizeof(double));
    if (!mat->data) {
        free(mat);
        return NULL;
    }
    mat->rows = rows;
    mat->cols = cols;
    return mat;
}

void cgemm_freeMat(matrix* mat) {
    if (mat) {
        free(mat->data);
        free(mat);
    }
}

void cgemm_fillMat(matrix* mat, const double* data) {
    memcpy(mat->data, data, mat->rows * mat->cols * sizeof(double));
}

void cgemm_printMat(matrix* mat) {
    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            printf("%.2f ", mat->data[j * mat->rows + i]);
        }
        printf("\n");
    }
}

void cgemm_gemm(const double* alpha, matrix* A, matrix* B, const double* beta, matrix* C, matrix* D) {
    size_t m = A->rows;
    size_t k = A->cols;
    size_t n = B->cols;
    
    double alpha_val = *alpha;
    double beta_val = *beta;
    
    // Compute D = alpha * A * B + beta * C
    for (size_t jj = 0; jj < n; jj++) {           // columns of result
        for (size_t ii = 0; ii < m; ii++) {       // rows of result
            // Compute D[ii, jj]
            double sum = 0.0;
            
            // Dot product of row ii of A with column jj of B
            for (size_t kk = 0; kk < k; kk++) {
                // A[ii, kk] in column-major: data[ii + kk * A->rows]
                // B[kk, jj] in column-major: data[kk + jj * B->rows]
                double a_val = A->data[ii + kk * A->rows];
                double b_val = B->data[kk + jj * B->rows];
                sum += a_val * b_val;
            }
            
            // D[ii, jj] = alpha * sum + beta * C[ii, jj]
            size_t idx = ii + jj * D->rows;
            D->data[idx] = alpha_val * sum + beta_val * C->data[idx];
        }
    }
}