#ifndef QUASI_NEWTON_HPP
#define QUASI_NEWTON_HPP

#include <SolverBase.hpp>

//QUASI-NEWTON
class QuasiNewton : public SolverBase
{
public:
    //constructor
    QuasiNewton()=default;
    //override solve method
    XType solve(SolverParameters params,FunctionType fun) override;
};

#endif //QUASI_NEWTON_HPP