#ifndef THETA_METHOD_HPP
#define THETA_METHOD_HPP

#include <vector>
#include <array>
#include <functional>
#include <string>

struct ThetaParams{
    //constructor 
    ThetaParams(const std::string &filename);

    //theta parameter
    double theta;
    //parameters that characterise CN
    double final_time;
    unsigned num_steps;
    //parameters for the newton solver
    double newt_tol;
    double newt_tola;
    unsigned newt_maxIt;
    //parameter to compute the derivative
    double der_step;
};

//define the output type of the solver
using theta_sol_type = std::array<std::vector<double>,2>;

class ThetaMethod{
    public:
        //constructor
        ThetaMethod(const std::string &filename);
        //solving method
        theta_sol_type operator()(const std::function<double(double,double)> fun, const double y0) const;

    private:
        ThetaParams m_params;
};

#endif /* THETA_METHOD_HPP */