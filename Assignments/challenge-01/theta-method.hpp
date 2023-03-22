#ifndef THETA_METHOD_HPP
#define THETA_METHOD_HPP

#include <vector>
#include <array>
#include <functional>

//define the output type of the solver method
using theta_sol_type = std::array<std::vector<double>,2>;


class ThetaMethod{
    public:
        //constructor
        ThetaMethod(const double theta,
                        const double final_time,
                        const unsigned num_steps,
                        const double newt_tol,
                        const double newt_tola,
                        const unsigned newt_maxIt,
                        const double h_step);
        //solving method
        theta_sol_type operator()(const std::function<double(double,double)> fun, const double y0);

    private:
        //theta parameter
        double m_theta;
        //parameters that characterise CN
        const double m_final_time;
        const unsigned m_num_steps;
        //parameters for the newton solver
        const double m_newt_tol;
        const double m_newt_tola;
        const unsigned m_newt_maxIt;
        //parameter to compute the derivative
        const double m_h_step;
};

#endif /* THETA_METHOD_HPP */