#include "Solver.hpp"
#include "Derivatives.hpp"

//QUASI-NEWTON
QuasiNewton::QuasiNewton(SolverParameters params,double discrStep): SolverBase(params), m_discrStep(discrStep){}

SolverTraits::ResultType QuasiNewton::solve()
{
  ResultType x_old = m_param.x0;
  ResultType x_new = m_param.x0;
  double res = m_param.tol_r+1;
  double incr = m_param.tol_i+1;

  size_t i = 0;
  while(res > m_param.tol_r && incr > m_param.tol_i && i < m_param.maxIt){
    auto der_approx = apsc::makeForwardDerivative<1>(m_param.fun,m_discrStep);
    x_new = x_old - m_param.fun(x_old)/der_approx(x_old);
    res = std::abs(m_param.fun(x_new));
    incr = std::abs(x_new - x_old);
    x_old = x_new;    
    i++;
  }
  return x_new;
}
