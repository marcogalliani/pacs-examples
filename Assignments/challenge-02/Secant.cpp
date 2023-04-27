#include <Secant.hpp>
#include "SolverProxy.hpp"

using ST = SolverTraits;

//SECANT METHOD
//overriden solver 
ST::XType Secant::solve(SolverParameters params,ST::FunctionType fun) 
{
  XType x_old = params.x0;
  XType x_new = params.x1; //casual param to generate the second point
  TollType res = std::abs(fun(x_new));
  TollType incr = std::abs(x_new - x_old);

  double scaling_factor = (fun(x_new)-fun(x_old))/(x_new-x_old);

  CountType it = 0;
  do{
    //computing x_old, x_new
    x_old = x_new;  
    x_new = x_new - fun(x_new)/scaling_factor;
    //computing residual and increment
    res = std::abs(fun(x_new));
    incr = std::abs(x_new - x_old);
    //computing the scaling factor for the next iteration 
    scaling_factor = (fun(x_new)-fun(x_old))/(x_new-x_old);
    //updating iterations 
    it++;
  }while ((res > params.tol_r && incr > params.tol_i && it < params.maxIt));
  
  return x_new;
}

//REGISTERING THE SOLVER IN THE FACTORY THROUGH THE CREATION OF A PROXY OBJ
namespace{
    SolverProxy<Secant> S_sol("Secant");
}