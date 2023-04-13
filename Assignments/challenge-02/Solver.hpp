#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include <functional>

//TRAITS
struct SolverTraits
{
    using ResultType = double;
};

//PARAMETERS
struct SolverParameters{
    std::function<double(double)> fun;
    double a,b; //exploration range
    double tol_r; //residual
    double tol_i; //increment
    double x0; 
    size_t maxIt;

    SolverParameters(std::function<double(double)> fun,double a, double b, double tol_r,double tol_i, double x0, size_t maxIt):
    fun(fun),a(a),b(b),tol_r(tol_r),tol_i(tol_i),x0(x0),maxIt(maxIt){};
};

//BASE CLASS
class SolverBase : public SolverTraits
{
protected:
    SolverParameters m_param;
public:
    SolverBase(SolverParameters param):m_param(param){};
    virtual ResultType solve()=0;

};

//QUASI-NEWTON
class QuasiNewton : public SolverBase
{
private:
    double m_discrStep;
public:
    QuasiNewton(SolverParameters params, double discrStep);
    ResultType solve() override;
};

/*
//BISECTION
class Bisection : public SolverBase
{
public:
    Bisection();
    ResultType solve() override;
};

//SECANT
class Secant : public SolverBase
{
private:
    double m_tola;
    unsigned m_maxIt;
public:
    Secant();
    ResultType solve() override;
};

//SOLVER FACTORY 
class SolverFactory
{
public: 
    std::unique_ptr<SolverBase> operator()(std::string SolverName);
};
*/

#endif //SOLVER_HPP