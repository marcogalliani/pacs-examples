#include <iostream>
#include <cassert>

#include "Bisection.hpp"
#include "SolverProxy.hpp"

using ST = SolverTraits;

//BISECTION METHOD
ST::XType Bisection::solve(SolverParameters params,ST::FunctionType fun){ 
  XType curr_a = params.a, curr_b = params.b;  
  XType mean_pt = (curr_b + curr_a)/2;

  //check if in the given there's a zero
  XType xtr_prod = fun(curr_a)*fun(curr_b);
  assert((xtr_prod < 0) && "To apply bisection we need f(a)*f(b)<0");

  size_t it = 0;
  TollType residual = std::abs(mean_pt);
  //iterating
  while(it < params.maxIt && residual > params.tol_r){
    //computing the mean point of the interval
    mean_pt = (curr_b + curr_a)/2;
    //switch
    xtr_prod = fun(curr_a)*fun(mean_pt);
    if (xtr_prod > 0){
      curr_a = mean_pt;
    }
    else{
      curr_b = mean_pt;
    }
    //compute the residual
    residual = std::abs(fun(mean_pt));
    //update the number of iterations
    it = it +1;
  }
  //return the result
  return mean_pt;
  std::cout << "Bisection method ends after " << it << " iterations" << std::endl;
}

//REGISTERING THE SOLVER IN THE FACTORY THROUGH THE CREATION OF A PROXY OBJ
namespace{
    SolverProxy<Bisection> S_sol("Bisection");
}