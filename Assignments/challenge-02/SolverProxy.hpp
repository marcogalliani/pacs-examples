#ifndef SOLVER_PROXY_HPP
#define SOLVER_PROXY_HPP

#include "SolverBase.hpp"
#include "SolverFactory.hpp"

template<class Solver>
class SolverProxy {
public: 
    using ST = SolverTraits;
    using SolverId = std::string;
    //constructor
    SolverProxy(SolverId const & id){
        ZeroFinders::Factory & solvers = ZeroFinders::solvers_factory; 
        solvers.add(id, &SolverProxy<Solver>::Build);
    }
    //Builder
    static std::unique_ptr<SolverBase> Build()
    {
        return std::make_unique<Solver>();
    }
};

#endif //SOLVER_PROXY_HPP