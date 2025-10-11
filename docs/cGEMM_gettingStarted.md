# cGEMM - Getting Started

## Welcome to cGEMM
Welcome.
This is probably the lightest c implementation of the gemm algorithm.
It makes no sense to use this package productively as you have access to way more sophisticated implementations.

If you are interested nonetheless, keep going!

## Overview
Let's make a quick tour through the project to give you a better understanding of what you are dealing with.

* `docs` contains all the info that might be necessary for you using it.

* `examples` contains runnable examples that show some use cases you can study.

* `external` contains third party sources.

* `test` contains all the tests that assure that the source code does what it is intended to do.

* `src` contains the actual source code. The heart of the project.

* `include` contains header files.

## How to Use
Here is a simple example of how to use cGEMM.

```c
#include "cGEMM.h"

/*

Consider the following 2x3 matrix

A = [
    [1, 2, 3],
    [4, 5, 6]
]

3x2 matrix

B = [
    [1, 2],
    [3, 4],
    [5, 6]
]

and the 2x2 matrix

C = [
    [1, 2],
    [3, 4]
]
*/

// allocate memory
matrix* A = cgemm_mallocMat(2, 3);
matrix* B = cgemm_mallocMat(3, 2);
matrix* C = cgemm_mallocMat(2, 2);

// fill in data (cGEMM assumes column major format)
const double valuesA[] = {1, 4, 2, 5, 3, 6};
const double valuesB[] = {1, 3, 5, 2, 3, 6};
const double valuesC[] = {1, 3, 2, 4};
cgemm_fillMat(A, valuesA);
cgemm_fillMat(B, valuesB);
cgemm_fillMat(C, valuesC);

// show matrix data
printf("A = \n");
cgemm_printMat(A);
printf("B = \n");
cgemm_printMat(B);
printf("C= \n");
cgemm_printMat(C);

// Let's compute D = alpha*A*B + beta*C
matrix* D = cgemm_mallocMat(2,2);
double alpha = 1.0;
double beta  = 2.0;
cgemm_gemm(&alpha, A, B, &beta, C, D);
printf("D = \n");
cgemm_printMat(D);


// free memory
cgemm_freeMat(A);
cgemm_freeMat(B);
cgemm_freeMat(C);
cgemm_freeMat(D);
```

This wraps it pretty much up!