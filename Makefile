CXX=g++
CXXFLAGS=-std=c++14 -fopenmp -O3
OUT=main
SRC=main.cc

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

check: clean all
	./main

clean:
	$(RM) $(OUT)
