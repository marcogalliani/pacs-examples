# PACS CHALLENGE 2: 2022-2023

## Code structure
The code is structured as follows:

- In `Secant.hpp`, `Bisection.hpp`, `QuasiNewton.hpp` and in the corresponding .cpp files the three different solvers are implemented as child classes of the virtual class `SolverBase`.
- I implemented an object factory (`SolverFactory.hpp`) to store the previous three methods. To implement it I used the singleton design pattern to have a single object factory in all my code. The registration of a `Solver` object in the factory is performed creating objects of `SolverProxy` class (`SolverProxy.hpp`). The factory is istantiated in `SolverFactory.cpp`
- The code is structured to have a plugin architecture. Thus, the three methods are first compiled with the `-fPIC` option and then the objects are stored in three different shared library loaded at run time with the `dlopen` utility

Thanks to this structure it is possible to compile just one time with the usual `make` and then change the parameters of the Solvers and the libraries loaded without the need to recompile by changing the files `SolverParameters.json` and `libraries.txt`