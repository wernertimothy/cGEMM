
#include "cGEMM.h"
#include "unity.h"

void setUp() {}
void tearDown() {}

void test_cgemm_mallocMat(void) {
    matrix* A = cgemm_mallocMat(2,3);
    TEST_ASSERT_NOT_NULL(A);
    TEST_ASSERT_EQUAL_size_t(2, A->rows);
    TEST_ASSERT_EQUAL_size_t(3, A->cols);
    cgemm_freeMat(A);
}

void test_cgemm_fillMat(void) {
    /*
    A = [
        [1, 2, 3],
        [4, 5, 6]
    ]
    */
   matrix* A = cgemm_mallocMat(2, 3);
   TEST_ASSERT_NOT_NULL(A);
   const double data[] = {1,4,2,5,3,6};
   cgemm_fillMat(A, data);
   TEST_ASSERT_EQUAL_DOUBLE_ARRAY(data, A->data, 2*3);
   cgemm_freeMat(A);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_cgemm_mallocMat);
    RUN_TEST(test_cgemm_fillMat);
    return UNITY_END();
}