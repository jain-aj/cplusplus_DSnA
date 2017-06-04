# c++_DSnA
C++ playground for data structure and algorithm programs.

## Dependency

* GoogleTest https://github.com/google/googletest

## Usage

1. Enter the directory for each problem and compile the source code.

```
g++ -c <problem_source_code>.cpp
```

2. Test with googleTest framework using the following command.

```
g++ test.cpp -o test <problem_source_code>.o -lgtest -lgtest_main
```
3. Run test to show the result

```
./test
```
## Problems

* ### Dynamic programming
  * matrix chain multiplication
  * optimal binary search tree
