#include "QuasiNewton.hpp"
#include "Derivatives.hpp"
#include "SolverProxy.hpp"

using ST = SolverTraits;

//QUASI-NEWTON METHOD
ST::XType QuasiNewton::solve(SolverParameters params, ST::FunctionType fun)
{
  XType x_old = params.x0;
  XType x_new = params.x0;
  TollType res = std::abs(fun(x_new));
  TollType incr = params.tol_i+1;
  //iterating
  CountType it = 0;
  while(res > params.tol_r && incr > params.tol_i && it < params.maxIt){
    auto der_approx = apsc::makeForwardDerivative<1>(fun,params.der_step);
    x_new = x_old - fun(x_old)/der_approx(x_old);
    res = std::abs(fun(x_new));
    incr = std::abs(x_new - x_old);
    x_old = x_new;    
    it++;
  }
  return x_new;
}

//REGISTERING THE SOLVER IN THE FACTORY THROUGH THE CREATION OF A PROXY OBJ
namespace{
    SolverProxy<QuasiNewton> S_sol("QuasiNewton");
}