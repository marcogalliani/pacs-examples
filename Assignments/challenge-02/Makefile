CXX      ?= g++
CXXFLAGS ?= -std=c++20

#specifying directory of the examples
PACS_ROOT?=/workspaces/pacs-examples/Examples

#including the header files
CPPFLAGS ?= -O3 -Wall -pedantic -I$(PACS_ROOT)/include \
            -isystem$(mkBoostInc) -isystem$(mkTbbInc)
#loading the shared libraries
LDLIBS   ?= -L$(mkBoostLib) -L$(mkTbbLib) \
            -lboost_iostreams -lboost_system -lboost_filesystem -ltbb

#telling the loader where to look for shared libraries
LDFLAGS ?= -Wl,-rpath=$(PACS_ROOT)/lib
#specify the linker
LINK.o := $(LINK.cc) 

DEPEND = make.dep

EXEC = main
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY = all $(EXEC) $(OBJS) clean distclean $(DEPEND)

all: $(DEPEND) $(EXEC)

$(EXEC): $(OBJS)

$(OBJS): %.o: %.cpp

clean:
	$(RM) $(DEPEND)
	$(RM) *.o
	$(RM) result.dat solution.png 


distclean: clean
	$(RM) $(EXEC)
	$(RM) *.csv *.out *.bak *~

$(DEPEND): $(SRCS)
	@$(RM) $(DEPEND)
	@for file in $(SRCS); \
	do \
	  $(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM $${file} >> $(DEPEND); \
	done

-include $(DEPEND)
