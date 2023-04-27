#ifndef SOLVER_FACTORY_HPP
#define SOLVER_FACTORY_HPP

#include "SolverBase.hpp"
#include <string> 
#include <map>

namespace ZeroFinders{
    using ST = SolverTraits;
    using SolverBuilder = std::function<std::unique_ptr<SolverBase>()>;
    using SolverId = std::string;
    using FactoryType = std::map<SolverId,SolverBuilder>;

    //I made the class final according the singleton design pattern
    class Factory final
    {
    private:
    //SINGLETON DESIGN PATTERN
        //we keep the defaul constructor private to control who can create
        //a factroy object
        Factory() = default;
    //MEMBERS
        FactoryType m_factory;
    public:
    //SINGLETON DESIGN PATTERN
        //deleting the synthesized copy constructor
        Factory(Factory const &) = delete;
        //deleting the synthesized assignment operator
        Factory & operator=(Factory const &) = delete;

        //create an instance of the Factory object
        //Indeed, only member function can create a factory object since
        //we made the constructor private. We exploit the proprties of static
        //variables in order to make the object available
        static Factory & Instance(){
            static Factory factory;
            return factory;
        }
    //FACTORY METHODS
        //creating a new object
        std::unique_ptr<SolverBase> create(SolverId solver_id);
        //method to add different solver routines to the factory 
        void add(SolverId sol_id, SolverBuilder sol_builder);
        //getter for the pointer to a specific solver
        SolverBuilder get(SolverId solver_id);
    };

    extern Factory & solvers_factory;
}


#endif //SOLVER_FACTORY_HPP