CXX      ?= g++
CXXFLAGS ?= -std=c++20

#including the header files
INCLUDE ?= -I. -Iinclude -isystem$(mkBoostInc) -isystem$(mkTbbInc)

CPPFLAGS ?= -O3 -Wall -pedantic 

#loading the shared libraries
LDLIBS   ?= -L$(mkBoostLib) -L$(mkTbbLib) -Llib\
            -lboost_iostreams -lboost_system -lboost_filesystem -ltbb -L. -ldl \
			-lmuparser

#telling the loader where to look for shared libraries
LDFLAGS ?= -Wl,-rpath=. -Wl,-rpath=lib

#specify the linker
LINK.o := $(LINK.cc) 

#gather all .cpp files
SRCS = $(wildcard *.cpp)

#solvers to compile
SOLVERS = QuasiNewton Bisection Secant

all: linking

objects: $(SRCS)
#compiling
	$(CXX) $(CXXFLAGS) ${INCLUDE} $(CPPFLAGS) -c main.cpp
#shared libraries
	for S in $(SOLVERS); do \
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(CPPFLAGS) -fPIC -c $$S.cpp; \
	$(CXX) -shared $$S.o -o lib$$S.so; \
	done

	$(CXX) $(CXXFLAGS) $(INCLUDE) $(CPPFLAGS) -fPIC -c SolverFactory.cpp 
	$(CXX) -shared SolverFactory.o -o libsolverFactory.so
	 
linking: objects
	$(CXX) $(LDFLAGS) $(LDLIBS) -L. -lsolverFactory main.o -o main

clean:
	$(RM) *.o
	$(RM) *.so

distclean: clean
	$(RM) $(EXEC)
	$(RM) *.csv *.out *.bak *~


