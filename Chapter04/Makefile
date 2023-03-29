CXX=clang++

CXXFLAGS=-std=c++14 -g

LINKS=-lSDL2 -lSDL2_image

DEPS=\
	Actor.o \
	AIComponent.o \
	AIState.o \
	Bullet.o \
	CircleComponent.o \
	Component.o \
	Enemy.o \
	Game.o \
	Grid.o \
	Math.o \
	MoveComponent.o \
	NavComponent.o \
	SpriteComponent.o \
 	Tile.o \
	Tower.o \

all: $(DEPS) Main.out

Main.out: Main.cpp $(DEPS)
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

clear:
	@rm -Rf *.out *.o 2>/dev/null