#include <iostream>
#include <vector>
#include <chrono.hpp>

// WORD MEMORY: architecture dependent -> 32-bit or 64-bit

struct Struct0 {
   uint64_t u64; // 8 bytes
   uint32_t u32; // 4 bytes
   // Padding here
};

class Struct1 {
  char c;       // 1 byte. +2 bytes of padding (see output)
  int i;        // 4 bytes.
  short int s;  // 2 bytes. +2 bytes of padding (see output)
};

class Sruct3{
  char c; //  1 byte
  short int s; //  2 bytes
  int i; //  4 bytes
}

int main() {
  using namespace std::chrono;

  {
  const auto t0 = high_resolution_clock::now();
  std::vector<Struct1> v1(100'000'000);
  const auto t1 = high_resolution_clock::now();
  const auto dt = duration_cas<milliseconds>(t1-t0).count();
  std::cout << "Size of Struct0 is " << sizeof(Struct0) << " bytes." << std::endl;
  std::cout << "Size of Struct1 is " << sizeof(Struct1) << " bytes." << std::endl;
  }
  return 0;
}
