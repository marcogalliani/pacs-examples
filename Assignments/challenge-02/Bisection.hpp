#ifndef BISECTION_HPP
#define BISECTION_HPP

#include <SolverBase.hpp>

//BISECTION
class Bisection : public SolverBase
{
public:
    //constructor
    Bisection()=default;
    //override solve method
    XType solve(SolverParameters params,FunctionType fun) override;
};

#endif //BISECTION_HPP 