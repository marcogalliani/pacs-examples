#include <chrono>
#include <cstdlib>

#include "matrix.hpp"

int main(int argc, char **argv) {
  const size_t matrix_size = argc > 1 ? std::atoll(argv[1]) : 1000; 
  std::cout << "matrix_size = " << matrix_size << std::endl;

  //instatiating and filling matrices
  matrix A(matrix_size);
  matrix B(matrix_size);
  for (size_t i = 0; i < matrix_size; ++i) {
    A(i, i) = 10.0;
    A(i, matrix_size - 1) = 30.0;
    B(i, 0) = 1.0;
    B(i, i) = 3.0;
  }

  //benchmarking the performance of transpositin and multiplication
  using namespace std::chrono;
  {
    const auto t0 = high_resolution_clock::now();
    //here it may seem that we're making an extra copy and that it could be useful to use std::move
    //However, there exists a compiler optimization that does just the same thing avoiding useless copies called return object optimization
    matrix C = A * B;
    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();
    std::cout << "Multiply time: " << dt << " [ms] " << std::endl;
  }
  {
    const auto t0 = high_resolution_clock::now();
    //here it may seem that we're making an extra copy and that it could be useful to use std::move
    //However, there exists a compiler optimization that does just the same thing avoiding useless copies called return object optimization
    matrix C = A.mmult_eigen(B);
    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();
    std::cout << "Multiply Eigen time: " << dt << " [ms] " << std::endl;
  }


  {
    const auto t0 = high_resolution_clock::now();
    matrix D = A.transpose();
    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();
    std::cout << "Transpose time: " << dt << " [ms] " << std::endl;
  }

  return 0;
}
