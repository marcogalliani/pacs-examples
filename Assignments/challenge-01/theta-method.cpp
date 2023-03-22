#include "theta-method.hpp"
#include "basicZeroFun.hpp"
#include "Derivatives.hpp"

#include <limits>
#include <iostream>
#include <tuple> //to use std::get


//constructor
ThetaMethod::ThetaMethod(const double theta,
                            const double final_time,
                            const unsigned num_steps,
                            const double newt_tol,
                            const double newt_tola,
                            const unsigned newt_maxIt,
                            const double h_step):
                            m_theta(theta),
                            m_final_time(final_time),
                            m_num_steps(num_steps),
                            m_newt_tol(newt_tol),
                            m_newt_tola(newt_tola),
                            m_newt_maxIt(newt_maxIt),
                            m_h_step(h_step)
{}

//solver
theta_sol_type
ThetaMethod::operator()(const std::function<double(double, double)> fun, const double y0)
{
    double h_step=m_final_time/m_num_steps; //computing discretisation step
    std::vector<double> th(m_num_steps+1); 
    //computing each time steps
    for(size_t i=1; i<th.size();i++)
        th[i]=th[i-1]+h_step;

    std::vector<double> uh(m_num_steps+1); 
    uh[0]=y0;

    for(size_t it=0; it<m_num_steps; it++){
        auto phi = [&](double u){return u - uh[it]-h_step*((1-m_theta)*fun(th[it],uh[it])+m_theta*fun(th[it+1],u));};
        //computing the derivative of phi
        auto d_phi=apsc::makeForwardDerivative<1>(phi,m_h_step);
        //Newton method
        auto zero = apsc::Newton(phi, d_phi, uh[it], m_newt_tol, m_newt_tola, m_newt_maxIt);
        
        //checking solution 
        if(std::get<1>(zero))
            uh[it+1] = std::get<0>(zero);
        else{
            std::cerr << "Newton failed to compute a solution for the given set of parameters" << std::endl;
            it=m_num_steps;
        }

    }
    theta_sol_type solution;
    solution[0] = th;
    solution[1] = uh;

    return solution;
}

