#get object file from .cpp
g++ Utilities.cpp -c -I../include -I${mkEigenInc} -fPIC

#get shared library from object files
g++ -shared Utilities.o -o liblinearalgebra.so

#compile test.cpp
module load suitesparse
g++ test.cpp -c -I../include -I${mkEigenInc} -I${mkSuitesparseInc}

#link test.o against liblinearalgebra.so
g++ liblinearalgebra.so test.o -o test -L${mkSuitesparseLib} -lumfpack

#direct the loader
export LD_LIBRARY_PATH+=:$PWD

#test the exexutable
./test
