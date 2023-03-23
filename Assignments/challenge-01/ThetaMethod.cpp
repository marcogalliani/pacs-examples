#include "ThetaMethod.hpp"

#include "basicZeroFun.hpp"
#include "Derivatives.hpp"

#include <cmath>
#include <string>
#include <limits>
#include <vector>
#include <iostream>
#include <tuple> //to use std::get

#include "json.hpp"
#include <fstream>

#include "gnuplot-iostream.hpp"

using json = nlohmann::json;

ThetaParams::ThetaParams(const std::string &filename){

    std::ifstream input_stream(filename.c_str());
  	json data = json::parse(input_stream);

	//SETTING METHOD PARAMETERS
	theta = data["theta_param"].value("theta",0.5);
	num_steps = data["theta_param"].value("n_steps",100);
	final_time = data["theta_param"].value("final_time",1);
	//Newton method parameters
	newt_tol = data["Newt_param"].value("tol",1e-3);
    newt_tola=data["Newt_param"].value("tola",1e-5);
    newt_maxIt = data["Newt_param"].value("maxIt",200);
	//increment to compute the derivative
	der_step = data["Newt_param"].value("der_step",1e-3);
}

//constructor
ThetaMethod::ThetaMethod(const std::string &filename):m_params(filename.c_str()){}

//solver
theta_sol_type
ThetaMethod::operator()(const std::function<double(double, double)> fun, const double y0) const
{
    double h_step = m_params.final_time/m_params.num_steps; //computing discretisation step
    //computing each time steps
    std::vector<double> th(m_params.num_steps+1); 
    for(size_t i=1; i<th.size();i++)
        th[i]=th[i-1]+h_step;

    std::vector<double> uh(m_params.num_steps+1); 
    uh[0]=y0;

    for(size_t it=0; it<m_params.num_steps; it++){
        //to find u_{n+1} we have to find the zero of the function phi(u) defined as follows, we'll rely on Newton method
        auto phi = [&](double u){return u - uh[it]-h_step*((1-m_params.theta)*fun(th[it],uh[it])+m_params.theta*fun(th[it+1],u));};
        //in order to use Newton we need the derivative of phi
        auto d_phi=apsc::makeForwardDerivative<1>(phi,m_params.der_step);
        //applying Newton method
        auto zero = apsc::Newton(phi, d_phi, uh[it], m_params.newt_tol, m_params.newt_tola, m_params.newt_maxIt);
        
        //checking solution 
        if(std::get<1>(zero))
            uh[it+1] = std::get<0>(zero);
        else{
            std::cerr << "Newton failed to compute a solution for the given set of parameters" << std::endl;
            it=m_params.num_steps;
        }

    }
    theta_sol_type solution;
    solution[0] = th;
    solution[1] = uh;

    return solution;
}





