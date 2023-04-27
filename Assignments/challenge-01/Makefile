CXX      ?= g++
CXXFLAGS ?= -std=c++20

#to use muparser (taken from the Makefile.inc given as an example)
MUPARSER_LIBDIR=-L./lib
MUPARSERX_LIBDIR=-L./lib
MUPARSERX_INCLUDE=-I./include/muparserx
LIBRARY_NAME=muParserInterface
STATIC_LIBFILE=lib$(LIBRARY_NAME).a
DYNAMIC_LIBFILE=lib$(LIBRARY_NAME).so

#including the header files
CPPFLAGS ?= -O3 -Wall -pedantic -I./include \
            -isystem$(mkBoostInc) -isystem$(mkTbbInc)
CPPFLAGS+=$(MUPARSER_INCLUDE) $(MUPARSERX_INCLUDE)
#loading the shared libraries
LDLIBS   = -L${mkBoostLib} -L${mkTbbLib} \
            -lboost_iostreams -lboost_system -lboost_filesystem -ltbb
LDLIBS+=-L. -l$(LIBRARY_NAME) $(MUPARSER_LIBDIR) -lmuparser \
-L$(MUPARSERX_LIBDIR) -lmuparserx -L./lib -lpacs
#telling the loader where to look for shared libraries
LDFLAGS ?= -Wl,-rpath=./lib
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
