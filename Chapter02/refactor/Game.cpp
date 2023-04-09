#include "Game.hpp"
#include "Ship.hpp"
#include "Background.hpp"
#include "SDL_Helper.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include <iostream>

using namespace std;

const static int SDL_INITIALIZATION_FLAGS = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

// We want the game to be updated 60 times in one second. 
const static int MILLISECONDS_BETWEEN_FRAMES = 1000/60;

// The game must not have a delta time to high, otherwise objects will just "transport" between locations
const static float MAXIMUM_DELTA_TIME = 0.05F;

Game::Game(const unsigned short width, const unsigned short heigth):
window(sdl_window_unique_ptr(create_window("Game Programming in C++ (Chapter 2) Refactored", width, heigth), &SDL_DestroyWindow)),
renderer(sdl_renderer_unique_ptr(create_renderer(window.get()), &SDL_DestroyRenderer)),
screen_size(Vector(width, heigth))
{
	if (SDL_Init(SDL_INITIALIZATION_FLAGS) != 0)
	{
        throw "Could not initialize SDL Video flags ...";
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
        throw "Could not load image module!";
	}
}

Game::~Game()
{
	SDL_Quit();    
}

void Game::process_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
		}
	}
    const unsigned char* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		running = false;
	}    
    for (const auto& actor : actors)
    {
        if (actor->state == ALIVE)
        {
            actor->input(state);
        }
    }
}

void Game::update_world()
{
    // Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), elapsed_milliseconds + MILLISECONDS_BETWEEN_FRAMES));

	float delta_time = (SDL_GetTicks() - elapsed_milliseconds) / 1000.0f;
    
    // If delta time is too high. This can happen when you are in the debugger. 
    // So we limit it to the maximum of 0.05f
    if (delta_time > MAXIMUM_DELTA_TIME)
    {
        delta_time = MAXIMUM_DELTA_TIME;
    }

    elapsed_milliseconds = SDL_GetTicks();

    for (const auto& actor : actors)
    {
        if (actor->state == ALIVE)
        {
            actor->update(delta_time);
        }
        else if (actor->state == DEAD)
        {
            // TODO
            // actors.erase(actor);
        }
    }

}

void Game::draw()
{

    SDL_Renderer* renderer = this->renderer.get();

    // Set the background to all black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

    for (const auto& actor : actors)
    {
        actor->draw(renderer);
    }  
    SDL_RenderPresent(renderer);  
}

void Game::run()
{
    actors.push_back(make_unique<BackgroundScrollableImage>(BackgroundScrollableImage(renderer.get(), screen_size)));
    // Since the ship must be in front of the background images, we must draw the background image first
    actors.push_back(make_unique<Ship>(Ship(renderer.get())));

    running = true;
    elapsed_milliseconds = SDL_GetTicks();
    while(running) 
    {   
        process_input();
        update_world();
        draw();
    }
}
