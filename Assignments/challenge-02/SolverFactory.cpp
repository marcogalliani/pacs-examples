#include "SolverFactory.hpp"

namespace ZeroFinders{
    //CREATE
    std::unique_ptr<SolverBase> Factory::create(SolverId solver_id){
        return get(solver_id)();
    }
    //ADD
    void Factory::add(SolverId sol_id, SolverBuilder sol_builder){
        m_factory.insert({sol_id,sol_builder});
    }
    //GET
    SolverBuilder Factory::get(SolverId solver_id){
        return m_factory.at(solver_id);
    }
    //ISTANTIATE A FACTORY OBJECT
    Factory & solvers_factory = Factory::Instance();
}