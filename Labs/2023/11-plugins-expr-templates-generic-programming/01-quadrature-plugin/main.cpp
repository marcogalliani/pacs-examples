#include <dlfcn.h>

#include <cmath>
#include <functional>
#include <iostream>
#include <numbers>

/* MAIN AND TRAPEZOIDAL.CPP ARE COMPLETELY INDFEPENDENT
* We can load dynamically just what is strictly needed for our program
*/

/* PROS & CONS
* -> dynamic library loading
* -> difficult to debug
*/

//Now we can run the program giving as an input the desired library to be loaded at runtime

double integrand(double x) { return std::sin(x * x) * std::sin(x * x); }

int main(int argc, char **argv) {

  if(argc < 2){
    std::cerr << "No library was specified" << std::endl;
    return 1;
  }

  //1. open the shared-library (the .so file)
  void *handle = dlopen(argv[1], RTLD_LAZY); //read the documentation in the solution to see what RTLD_LAZY means
  //safety check
  if(!handle){ //handle == nullptr
    std::cerr << "cannot load the library" << std::endl;
    std::cerr << dlerror() << std::endl;
    return 1; //std::exit(1);
  }
  
  //2. read a symbol
  void *sym = dlsym(handle, "integrate");
  //safety check
  if(!sym){ //handle == nullptr
    std::cerr << "cannot load the symbol" << std::endl;
    std::cerr << dlerror() << std::endl;
    return 1; //std::exit(1);
  }

  //3. cast our symbol to our object
  double (* integrate)(const std::function<double(double)> &, double, double); //we're declaring an integrate variable 
  integrate = reinterpret_cast<decltype(integrate)>(sym);
  //the most similar to the direct C cast
  //same role of static_cast, dynamic_cast


  //We're done, we can evaluate it 
  const double res = integrate(integrand, 0, std::numbers::pi_v<double>);

  std::cout << "res = " << res << std::endl;

  return 0;
}
