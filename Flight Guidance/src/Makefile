EXENAME = openflight
OBJS = main.o graph.o utils.o airport.o edge.o bfs.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm



$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)
main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp
graph.o : graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp
utils.o : utils.cpp
	$(CXX) $(CXXFLAGS) utils.cpp
airport.o : airport.cpp
	$(CXX) $(CXXFLAGS) airport.cpp
edge.o : edge.cpp
	$(CXX) $(CXXFLAGS) edge.cpp
bfs.o : bfs.cpp
	$(CXX) $(CXXFLAGS) bfs.cpp

clean :
	-rm -f *.o $(EXENAME) test


# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

output_msg: ; $(CLANG_VERSION_MSG)

test: output_msg tests.o graph.o utils.o edge.o bfs.o airport.o
	$(LD) tests.o graph.o utils.o edge.o bfs.o airport.o $(LDFLAGS) -o test

tests.o: tests/tests.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/tests.cpp
    
.PHONY: output_msg