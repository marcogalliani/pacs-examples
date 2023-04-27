# CHALLENGE 1

## Compiling
To compile the code is necessary to have the boost library loaded, which was not default in the pacs repository. For this reason `module load boost` is required before `make` if not already loaded.

## Code structure
- The solver is implemented as a functor in the files `ThetaMethod.hpp` and `ThetaMethod.cpp`
- The parameters of the method are stored in a struct always declared and defined in `ThetaMethod.hpp` and `ThetaMethod.cpp`. In particular, the struct has a constructor that takes as input the name of the json file from which the parameters are parsed.
- Two json files are present to specify both the method paramaters (`params.json`) and some parameters to test the method (`testing_params.json`). The function is parsed with muParserX.
- The programm outputs a file `result.dat` to store the results and a file `solution.png`, which contains the plot of the solution.
