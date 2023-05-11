#include <chrono>
#include <iostream>
#include <vector>


//The reason behind loop unrolling is that comparison operations are costly. Unrolling the loops allows us to reduce the number of comparison op.
//However, it is not a technique to be implemented explicitly, the compiler can managing (if we tell him to do with the correct compiling options)

inline static constexpr size_t vec_size = 1000;

int multiply(const std::vector<int> &data) {
  int result = 1;

  for (const auto &v : data) {
    result *= v;
  }

  return result;
}

using timer = std::chrono::high_resolution_clock;

int main(int argc, char **argv) {
  const size_t n_iterations = 1e7;

  // Generate an arbitrary dataset.
  auto data = std::vector<int>(vec_size, 1);

  using namespace std::chrono;

  auto start = timer::now();
  double result;
  for (size_t i = 0; i < n_iterations; ++i) {
    result = multiply(data);
  }
  auto end = timer::now();

  std::cout << "Multiply: " << duration_cast<milliseconds>(end - start).count()
            << " ms, result: " << result << std::endl;

  return 0;
}
