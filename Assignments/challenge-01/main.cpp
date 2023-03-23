#include <iostream>
#include <cmath>
#include <fstream>

#include "ThetaMethod.hpp"
#include "json.hpp"
#include "muParserXInterface.hpp"
#include "gnuplot-iostream.hpp" // interface with gnuplot

using json = nlohmann::json;
using namespace MuParserInterface;

int main(){
	//PARSING DATA FROM JSON
	std::ifstream input("testing_params.json");
  	json data = json::parse(input);

	//TESTING PARAMETERS (fun, y0)
	const std::string fun_str  = data["testing"].value("fun", "-x[0]*exp(-x[1])");
    muParserXInterface<2> fun_parser(fun_str);
	//here I need an helper function that transforms the two distinct inputs in a unique vector
	auto fun = [&](double x, double y){return fun_parser({x,y});};

	double y0 = data["testing"].value("init_pt", 0.0);

	//APPLYING THETA METHOD
	ThetaMethod ThetaSolver("params.json");
	theta_sol_type PC_sol = ThetaSolver(fun,y0);

	//CHECKING THE METHOD RESULTS
	//initialize a vector to store the exact solution
	std::vector<double> exact_sol(PC_sol[0].size());
	
	const std::string ex_y_str = data["testing"].value("exact_y", "log(1-(x[0]^2)/2)");
    muParserXInterface<1> ex_y_parser(ex_y_str);
	//here I need an helper function that transforms the two distinct inputs in a unique vector
	auto ex_y = [&](double x){return ex_y_parser({x});};

	//WRITE RESULTS IN result.dat
	std::ofstream f("result.dat");
	f << "#time_step\tcomputed_sol\texact_sol" << std::endl;
	for(size_t i = 0; i < PC_sol[0].size(); ++i){
		exact_sol[i] = ex_y(PC_sol[0][i]);
		f << PC_sol[0][i] << "\t\t" << PC_sol[1][i] << "\t\t" << exact_sol[i] << "\n";
	}

	//PLOTTING THE RESULTS IN solution.png
	Gnuplot gp;
	gp << "set term png" << std::endl;
	gp << "set output 'solution.png'" << std::endl;
	gp << "plot" << gp.file1d(std::tie(PC_sol[0], PC_sol[1])) << "w lp lw 2 title 'uh',"
		<< gp.file1d(std::tie(PC_sol[0], exact_sol)) << "w lp lw 2 title 'exact solution'" << std::endl;


	return 0;
}