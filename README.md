# cGEMM

Welcome to cGEMM.
A very lightweight implementation of the [gemm](https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms#Level_3) algorithm in ANSI C.

This project is for mere educational purposes and serves as a C project example.
It provides a simple Matrix typedef and a general matrix matrix multiplication.

## Getting Started
You can find a [getting started][] in the [docs][] folder.

## API Documentation
For a complete reference of all functions and data structures, see the [API documentation][api].
The API provides functions for matrix memory management, data manipulation, and the GEMM operation.

## Build
```bash
mkdir build
cd build
cmake ..
make
```

You are now able to run the examples and use the code in your own projects.

## Testing
This project uses [Unity](https://github.com/ThrowTheSwitch/Unity) for testing.
Head over to their amazing page and check it out!
The sources of *Unity* are included under [unity][].


[getting started]: docs/cGEMM_gettingStarted.md
[docs]: docs/
[api]: docs/cgemm_API.md
[unity]: external/unity/