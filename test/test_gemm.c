#include "cGEMM.h"
#include "unity.h"

void setUp() {}
void tearDown() {}

void test_gemm(void) {
        // allocate memory
    matrix* A = cgemm_mallocMat(2, 3);
    matrix* B = cgemm_mallocMat(3, 2);
    matrix* C = cgemm_mallocMat(2, 2);
    matrix* D = cgemm_mallocMat(2, 2);

    // fill in data (cGEMM assumes column major format)
    const double valuesA[] = {1, 4, 2, 5, 3, 6};
    const double valuesB[] = {1, 3, 5, 2, 4, 6};
    const double valuesC[] = {1, 3, 2, 4};
    cgemm_fillMat(A, valuesA);
    cgemm_fillMat(B, valuesB);
    cgemm_fillMat(C, valuesC);

    // set factors
    const double alpha = 1.0;
    const double beta  = 2.0;

    // call gemm
    cgemm_gemm(&alpha, A, B, &beta, C, D);

    // test
    const double expectedRestuls[] = {24, 55, 32, 72};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expectedRestuls, D->data, 4);

    // free memory
    cgemm_freeMat(A);
    cgemm_freeMat(B);
    cgemm_freeMat(C);
    cgemm_freeMat(D);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_gemm);
    return UNITY_END();
}