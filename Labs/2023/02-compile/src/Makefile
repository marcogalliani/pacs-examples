compile-Utilities: Utilities.cpp
	g++ Utilities.cpp -c -I../include -I${mkEigenInc} -fPIC

make-shared: Utilities.o
	g++ -shared Utilities.o -o liblinearalgebra.so

compile-test: test.cpp 
	module load suitesparse
	g++ test.cpp -c -I../include -I${mkEigenInc} -I${mkSuitesparseInc}

link-test: test.o liblinearalgebra.so 
	g++ liblinearalgebra.so test.o -o test -L${mkSuitesparseLib} -lumfpack
	
execute: test
	export LD_LIBRARY_PATH+=:$PWD
	./test

clear:
	rm test test.o Utilities.o liblinearalgebra.so


