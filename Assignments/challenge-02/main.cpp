#include <cmath>
#include "muparser_fun.hpp"
#include "SolverFactory.hpp"
#include "LibraryLoader.hpp"

using json = nlohmann::json;
using ST = SolverTraits;

int main(){
    //FUNCTION TO TEST
    std::ifstream input("SolverParameters.json");
    json data = json::parse(input);
    const std::string fun_str = data["Testing"].value("fun", "0.5 - exp(pi*x)");
    MuparserFun fun(fun_str);

    //ADDING LIBRARIES
    LibraryLoader loader("libraries.txt");
    loader.print();

    //RESULTS
    std::cout << "\nRESULTS" << std::endl;
    //QuasiNewton
    if(loader.is_loaded("libBisection.so")){
        std::cout << "BISECTION METHOD: " << std::endl;
        std::cout << "result: " << ZeroFinders::solvers_factory.create("Bisection")->solve(SolverParameters("SolverParameters.json"),fun) << std::endl;
    }
    //Bisection
    if(loader.is_loaded("libQuasiNewton.so")){
        std::cout << "QUASI NEWTON METHOD: " << std::endl;
        std::cout << "result: " << ZeroFinders::solvers_factory.create("QuasiNewton")->solve(SolverParameters("SolverParameters.json"),fun) << std::endl;
    }
    //Secant
    if(loader.is_loaded("libSecant.so")){
        std::cout << "SECANT METHOD: " << std::endl;
        std::cout << "result: " << ZeroFinders::solvers_factory.create("Secant")->solve(SolverParameters("SolverParameters.json"),fun) << std::endl;
    }

    return 0;
}