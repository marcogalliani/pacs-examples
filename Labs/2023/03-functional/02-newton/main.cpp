#include "newton.hpp"
#include <iostream>

double fun(double x){
  return x*x*x+5*x+3;
}

double dfun(double x){
  return 3*x*x+5;
}

int
main(int argc, char **argv)
{

  const double toll_res=1e-8;
  const double toll_incr=1e-8;
  const unsigned max_it = 100;
  const double x0=.3;


  NewtonSolver solver(fun,dfun,toll_res,toll_incr,ax_iter);
  solver.solve(x0);
  std::cout << 
}
