#ifndef SECANT_HPP
#define SECANT_HPP

#include <SolverBase.hpp>

//BISECTION
class Secant : public SolverBase
{
public:
    //constructors
    Secant()=default;
    //override solve method
    XType solve(SolverParameters params,FunctionType fun) override;
};

#endif //SECANT_HPP