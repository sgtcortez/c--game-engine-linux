// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.hpp"

#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{

	Game game(1024, 768);
	game.run();
	return 0;
}
