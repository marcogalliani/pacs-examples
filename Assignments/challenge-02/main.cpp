#include <cmath>
#include <numbers>
#include <iostream>

#include "Solver.hpp"

int main(){

    auto fun = [&](double x){return 0.5 - std::exp(std::numbers::pi*x); };

    SolverParameters params(fun,-1,0, 1e-4,1e-4, -0.5, 100000);
    QuasiNewton QN_solver(params,1e-4);

    std::cout << "The result is: " << QN_solver.solve() << std::endl;

    return 0;
}