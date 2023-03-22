#include <iostream>
#include <cmath>
#include <fstream>

#include "theta-method.hpp"
#include "json.hpp"
#include "muParserXInterface.hpp"
#include "gnuplot-iostream.hpp" // interface with gnuplot

using json = nlohmann::json;
using namespace MuParserInterface;

int main(){
	//PARSING DATA FROM JSON
	std::ifstream input("parameters.json");
  	json data = json::parse(input);

	//SETTING METHOD PARAMETERS
	double theta = data["theta_param"].value("theta",0.5);
	unsigned n_steps = data["theta_param"].value("n_steps",100);
	double final_time = data["theta_param"].value("final_time",1);
	//Newton method parameters
	double newt_tol = data["Newt_param"].value("tol",1e-3), newt_tola=data["Newt_param"].value("tola",1e-5);
	unsigned newt_maxIt = data["Newt_param"].value("maxIt",200);
	//increment to compute the derivative
	double h_step = data["Newt_param"].value("der_step",1e-3);

	//TESTING PARAMETERS (fun, y0)
	const std::string fun_str  = data["testing"].value("fun", "-t*exp(-y)");
    muParserXInterface<2> fun_parser(fun_str);
	auto fun = [&](double x, double y){return fun_parser({x,y});};

	double y0 = data["testing"].value("init_pt", 0.0);

	//APPLYING THETA METHOD
	ThetaMethod ThetaSolver(theta,final_time,n_steps,newt_tol,newt_tola,newt_maxIt,h_step);
	theta_sol_type PC_sol = ThetaSolver(fun,y0);

	std::vector<double> exact_sol(n_steps+1);

	//WRITE RESULTS IN result.dat
	std::ofstream f("result.dat");
	f << "#time_step\tcomputed_sol\texact_sol" << std::endl;
	for(size_t i = 0; i <= n_steps; ++i){
		exact_sol[i] = std::log(1-PC_sol[0][i]*PC_sol[0][i]/2);
		f << PC_sol[0][i] << "\t\t" << PC_sol[1][i] << "\t\t" << exact_sol[i] << "\n";
	}

	//PLOTTING THE RESULTS IN solution.png
	Gnuplot gp; // gnuplot iostream! Plots solution on the screen
	// It may not work on virtual machines. Take it out in that case
	// Using temporary files (another nice use of tie)
	// Comment this statement if you are not using gnuplot iostream
	// to plot the solution directly on the terminal
	gp << "set term png" << std::endl;
	gp << "set output 'solution.png'" << std::endl;
	gp << "plot" << gp.file1d(std::tie(PC_sol[0], PC_sol[1])) << "w lp lw 2 title 'uh',"
		<< gp.file1d(std::tie(PC_sol[0], exact_sol)) << "w lp lw 2 title 'exact solution'" << std::endl;

	//COMPUTING THE CONVERGENCE ORDER (it should be O(h^2))
	double diff_max=0;
	double curr_d = 0;
	for (size_t i=0; i<PC_sol[0].size(); i++)
	{
		curr_d=  std::abs(PC_sol[1][i]-exact_sol[i]);
		if(curr_d > diff_max)
			diff_max = curr_d;
	}
	std::cout << "The computed convergence order is: " << diff_max << std::endl;
	std::cout << "The theorical convergence order is: " << final_time*final_time/(n_steps*n_steps) << std::endl;

	return 0;
}