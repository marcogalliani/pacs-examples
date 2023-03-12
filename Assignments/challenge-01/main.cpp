#include <iostream>
#include <cmath>
#include <fstream>

#include "CrankNicholson.hpp"
#include "json.hpp"
#include "muParserXInterface.hpp"

using json = nlohmann::json;
using namespace MuParserInterface;

int main(){
	//PARSING DATA FROM JSON
	std::ifstream input("data.json");
  	json data = json::parse(input);

	//SETTING METHOD PARAMETERS
	unsigned n_steps = data["CN_param"].value("n_steps",100);
	double final_time = data["CN_param"].value("final_time",1);
	//Newton method parameters
	double newt_tol = data["Newt_param"].value("tol",1e-3), newt_tola=data["Newt_param"].value("tola",1e-5);
	unsigned newt_maxIt = data["Newt_param"].value("maxIt",200);
	//increment to compute the derivative
	double h_step = data["Newt_param"].value("der_step",1e-3);

	//TESTING
	const std::string fun_str  = data["testing"].value("fun", "-t*exp(-y)");
    muParserXInterface<2> fun_parser(fun_str);
	auto fun = [&](double x, double y){return fun_parser({x,y});};

	double y0 = data["testing"].value("init_pt", 0.0);

	//APPLYING CRANK-NICHOLSON
	CrankNicholson CNsolver(final_time,n_steps,newt_tol,newt_tola,newt_maxIt,h_step);
	CN_type_sol PC_sol = CNsolver.solve(fun,y0);

	//WRITE RESULTS IN result.dat
	std::ofstream f("result.dat");
	f << "#index\ttime_step\tcomputed_sol" << std::endl;
	for(size_t i = 0; i <= n_steps; ++i){
		f << i << "\t\t" << PC_sol[0][i] << "\t\t" << PC_sol[1][i] << "\n";
	}

	return 0;
}