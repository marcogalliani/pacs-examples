#include "trapezoidal.hpp"

#include <cmath>

double integrate(const std::function<double(double)> &f, double a, double b){
    return (b-a)*(0.5*(f(b)-f(a)));
}