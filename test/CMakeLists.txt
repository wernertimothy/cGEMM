
add_executable(test_matrix
    test_matrix.c
    ${CMAKE_SOURCE_DIR}/external/unity/src/unity.c
)
add_executable(test_gemm
    test_gemm.c
    ${CMAKE_SOURCE_DIR}/external/unity/src/unity.c
)

target_compile_definitions(test_matrix PRIVATE UNITY_INCLUDE_DOUBLE)
target_compile_definitions(test_gemm PRIVATE UNITY_INCLUDE_DOUBLE)

target_link_libraries(test_matrix ${LIB_NAME})
target_link_libraries(test_gemm ${LIB_NAME})

target_include_directories(test_matrix PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/unity/src
)
target_include_directories(test_gemm PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/unity/src
)

enable_testing()
add_test(NAME test_matrix COMMAND test_matrix)
add_test(NAME test_gemm COMMAND test_gemm)