# cGEMM API Reference

This document provides a complete reference for all functions available in the cGEMM library.

## Overview

The cGEMM library provides a simple interface for matrix operations with a focus on the GEMM (General Matrix Multiply) algorithm. All matrices use **column-major storage format** (like Fortran and BLAS libraries).

## Data Structure

### matrix

```c
typedef struct {
    double* data;
    size_t rows;
    size_t cols;
} matrix;
```

Represents a matrix stored in column-major format.

- `data`: Pointer to a contiguous array of doubles storing matrix elements
- `rows`: Number of rows in the matrix
- `cols`: Number of columns in the matrix

**Storage Layout**: Element at row `i`, column `j` is located at index `i + j * rows` in the data array.

## Memory Management Functions

### cgemm_mallocMat

```c
matrix* cgemm_mallocMat(size_t rows, size_t cols);
```

Allocates memory for a new matrix.

**Parameters:**
- `rows`: Number of rows for the matrix
- `cols`: Number of columns for the matrix

**Returns:**
- Pointer to newly allocated matrix structure
- `NULL` if allocation fails

**Notes:**
- The matrix data is allocated but not initialized
- Always check return value for `NULL` before use
- Must be freed with `cgemm_freeMat()` to avoid memory leaks

**Example:**
```c
matrix* A = cgemm_mallocMat(3, 3);
if (A == NULL) {
    // Handle allocation error
}
```

### cgemm_freeMat

```c
void cgemm_freeMat(matrix* mat);
```

Frees memory allocated for a matrix.

**Parameters:**
- `mat`: Pointer to matrix to be freed (can be `NULL`)

**Notes:**
- Safe to call with `NULL` pointer
- Frees both the data array and the matrix structure
- Always call this function when done with a matrix

**Example:**
```c
matrix* A = cgemm_mallocMat(3, 3);
// ... use matrix ...
cgemm_freeMat(A);
```

## Data Management Functions

### cgemm_fillMat

```c
void cgemm_fillMat(matrix* mat, const double* data);
```

Fills a matrix with data from an array.

**Parameters:**
- `mat`: Pointer to the matrix to fill
- `data`: Pointer to array containing values in column-major order

**Notes:**
- The data array must contain at least `rows * cols` elements
- Data is copied into the matrix (original array can be freed afterwards)
- Data must be provided in column-major format

**Example:**
```c
matrix* A = cgemm_mallocMat(2, 3);

// For the matrix:
// [ 1  2  3 ]
// [ 4  5  6 ]
//
// Provide data in column-major order (column by column):
const double values[] = {1, 4, 2, 5, 3, 6};
//                       col0  col1  col2

cgemm_fillMat(A, values);
```

## Visualization Functions

### cgemm_printMat

```c
void cgemm_printMat(matrix* mat);
```

Prints a matrix to standard output in human-readable row-major format.

**Parameters:**
- `mat`: Pointer to the matrix to print

**Notes:**
- Displays matrix in traditional row-major format for readability
- Each element is formatted with 2 decimal places
- Useful for debugging and verification

**Example:**
```c
matrix* A = cgemm_mallocMat(2, 2);
const double values[] = {1, 3, 2, 4};
cgemm_fillMat(A, values);

printf("Matrix A:\n");
cgemm_printMat(A);
// Output:
// 1.00 2.00
// 3.00 4.00
```

## Computational Routines

### cgemm_gemm

```c
void cgemm_gemm(const double* alpha, matrix* A, matrix* B,
                const double* beta, matrix* C, matrix* D);
```

Performs the General Matrix Multiply operation: **D = α·A·B + β·C**

**Parameters:**
- `alpha`: Pointer to scalar multiplier for the matrix product A·B
- `A`: Pointer to first input matrix (m × k)
- `B`: Pointer to second input matrix (k × n)
- `beta`: Pointer to scalar multiplier for matrix C
- `C`: Pointer to third input matrix (m × n)
- `D`: Pointer to output matrix (m × n)

**Dimension Requirements:**
- A must be m × k
- B must be k × n
- C must be m × n
- D must be m × n
- No dimension validation is performed; incorrect dimensions cause undefined behavior

**Notes:**
- Scalar parameters are passed as pointers (following BLAS convention)
- D can be the same as C for in-place operation: `D = α·A·B + β·D`
- All matrices must use column-major storage
- No matrix transposition is performed

**Example:**
```c
// Compute D = 2.0 * A * B + 0.5 * C
matrix* A = cgemm_mallocMat(2, 3);  // 2x3 matrix
matrix* B = cgemm_mallocMat(3, 2);  // 3x2 matrix
matrix* C = cgemm_mallocMat(2, 2);  // 2x2 matrix
matrix* D = cgemm_mallocMat(2, 2);  // 2x2 matrix

// Fill matrices with data...
const double valuesA[] = {1, 4, 2, 5, 3, 6};
const double valuesB[] = {1, 3, 5, 2, 4, 6};
const double valuesC[] = {1, 3, 2, 4};

cgemm_fillMat(A, valuesA);
cgemm_fillMat(B, valuesB);
cgemm_fillMat(C, valuesC);

double alpha = 2.0;
double beta = 0.5;

cgemm_gemm(&alpha, A, B, &beta, C, D);

// Clean up
cgemm_freeMat(A);
cgemm_freeMat(B);
cgemm_freeMat(C);
cgemm_freeMat(D);
```

## Column-Major Storage Format

Understanding column-major storage is crucial for using cGEMM correctly.

### What is Column-Major Format?

In column-major format, matrix elements are stored column by column in a contiguous array.

For a 3×2 matrix:
```
[ a  b ]
[ c  d ]
[ e  f ]
```

The memory layout is: `[a, c, e, b, d, f]`

### Accessing Elements

To access element at row `i`, column `j`:
```c
double element = mat->data[i + j * mat->rows];
```

### Filling Matrices

When creating data arrays to fill matrices, arrange values by columns:

```c
// For matrix:
// [ 1  3  5 ]
// [ 2  4  6 ]

const double data[] = {
    1, 2,    // first column
    3, 4,    // second column
    5, 6     // third column
};
```

### Why Column-Major?

Column-major format is standard in Fortran, BLAS, and LAPACK libraries. This format can offer performance benefits for certain algorithms and makes the library compatible with other scientific computing tools.

## Complete Usage Example

```c
#include <stdio.h>
#include "cGEMM.h"

int main() {
    // Create matrices for: D = 1.0*A*B + 2.0*C

    // A is 2x3
    matrix* A = cgemm_mallocMat(2, 3);
    const double valuesA[] = {1, 4, 2, 5, 3, 6};  // column-major
    cgemm_fillMat(A, valuesA);

    // B is 3x2
    matrix* B = cgemm_mallocMat(3, 2);
    const double valuesB[] = {1, 3, 5, 2, 4, 6};  // column-major
    cgemm_fillMat(B, valuesB);

    // C is 2x2
    matrix* C = cgemm_mallocMat(2, 2);
    const double valuesC[] = {1, 3, 2, 4};  // column-major
    cgemm_fillMat(C, valuesC);

    // D is 2x2 (output)
    matrix* D = cgemm_mallocMat(2, 2);

    // Set scalars
    double alpha = 1.0;
    double beta = 2.0;

    // Perform computation
    cgemm_gemm(&alpha, A, B, &beta, C, D);

    // Display result
    printf("Result D = alpha*A*B + beta*C:\n");
    cgemm_printMat(D);

    // Clean up
    cgemm_freeMat(A);
    cgemm_freeMat(B);
    cgemm_freeMat(C);
    cgemm_freeMat(D);

    return 0;
}
```

## Error Handling

The cGEMM library performs minimal error checking:

- `cgemm_mallocMat()` returns `NULL` on allocation failure
- `cgemm_freeMat()` safely handles `NULL` pointers
- No dimension validation is performed in `cgemm_gemm()`

**User Responsibilities:**
- Check return values from allocation functions
- Ensure matrix dimensions are compatible before operations
- Avoid passing `NULL` pointers to functions (except `cgemm_freeMat`)
- Manage memory properly to avoid leaks
