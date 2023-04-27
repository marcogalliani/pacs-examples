#ifndef SOLVER_BASE_HPP
#define SOLVER_BASE_HPP


#include <memory>
#include <functional>
#include <string>
//to parse data from files
#include <fstream>
#include "json.hpp"

//TRAITS
struct SolverTraits
{
    using XType = double;
    using FunctionType = std::function<double(double)>;
    using TollType = double;
    using OptionsType = std::string;
    using CountType = size_t;
};

//PARAMETERS
struct SolverParameters: public SolverTraits{
    using json = nlohmann::json;
    //common parameters
    TollType tol_r; //residual
    TollType tol_i; //increment
    XType x0,x1; 
    CountType maxIt;

    //special parameters
    //QUASI NEWTON
    double der_step;
    //BISECTION
    XType a,b;

    SolverParameters(OptionsType filename){
        //read from files
        std::ifstream input(filename);
    	json data = json::parse(input);
        
        //parse data:
        //COMMON PARAMETERS
        tol_r = data["Common parameters"].value("tol_r",1e-3);
        tol_i = data["Common parameters"].value("tol_i",1e-3);
        x0 = data["Common parameters"].value("x0",-0.5);
        maxIt = data["Common parameters"].value("der_step",300);
        //SPECIAL PARAMETERS
        //Quasi-Newton
        der_step = data["Quasi-Newton"].value("der_step",1e-3);
        //Bisection
        a = data["Bisection"].value("lower bound",-1);
        b = data["Bisection"].value("upper bound",0);
        //Secant
        x1 = data["Secant"].value("x1",-0.75);
    }
};

//BASE CLASS
class SolverBase : public SolverTraits
{
public:
    using ST = SolverTraits;
    //constructor
    SolverBase()=default;
    //virtual solve method
    virtual XType solve(SolverParameters params,FunctionType fun)=0;
};

#endif //SOLVER_BASE_HPP