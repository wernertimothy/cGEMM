#include <stdio.h>
#include "cGEMM.h"

int main() {
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

    /*
    Let's compute D = alpha*A*B + beta*C
    */
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
}