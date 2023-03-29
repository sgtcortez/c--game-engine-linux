CXX=clang++

CXXFLAGS=-std=c++14 -g

LINKS=-lSDL2

DEPS=\
	Game.o \

all: $(DEPS) Main.out

Main.out: Main.cpp $(DEPS)
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

clear:
	@rm -Rf *.out *.o 2>/dev/null