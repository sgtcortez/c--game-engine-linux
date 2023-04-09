CXX=clang++

# User defined variables. 
# Example: make OTHER_FLAGS="-g -DDEBUG=1"
OTHER_FLAGS=

CXXFLAGS=-std=c++14 ${OTHER_FLAGS} 

LINKS=-lSDL2 -lSDL2_image

DEPS=\
	Component.o \
	Actor.o \
	Game.o \
	Ship.o \
	SDL_Helper.o \
	Background.o \

all: $(DEPS) Main.out

Main.out: Main.cpp $(DEPS)
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

clear:
	@rm -Rf *.out *.o 2>/dev/null