CXX=clang++

CXXFLAGS=-std=c++14 -g

LINKS=-lSDL2 -lSDL2_image

DEPS=\
	Actor.o \
	AnimSpriteComponent.o \
	BGSpriteComponent.o \
	Component.o \
	Game.o \
	Math.o \
	Ship.o \
	SpriteComponent.o \

all: $(DEPS) Main.out refactor_version

Main.out: Main.cpp $(DEPS)
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

refactor_version:
	$(MAKE) -C refactor -f Makefile

clear:
	@rm -Rf *.out *.o 2>/dev/null
	$(MAKE) -C refactor -f Makefile clear