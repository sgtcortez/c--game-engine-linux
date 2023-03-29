CXX=clang++

CXXFLAGS=-std=c++14 -g

LINKS=-lSDL2 -lSDL2_image

DEPS=\
	Actor.o \
	Asteroid.o \
	CircleComponent.o \
	Component.o \
	Game.o \
	InputComponent.o \
	Laser.o \
	Math.o \
	MoveComponent.o \
	Random.o \
	Ship.o \
	SpriteComponent.o \

all: $(DEPS) Main.out

Main.out: Main.cpp $(DEPS)
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

clear:
	@rm -Rf *.out *.o 2>/dev/null