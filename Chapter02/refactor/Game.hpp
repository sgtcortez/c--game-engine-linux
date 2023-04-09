#pragma once

#include "Actor.hpp"


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <vector>
#include <memory> 

// https://en.cppreference.com/w/cpp/memory/unique_ptr

/**
 * Since those structures(SDL_Window, SDL_Renderer) are C structures, they dont have a desctructor, like C++ 
 * So, we need to destroy them using their specified methods 
*/
using sdl_window_unique_ptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>; 
using sdl_renderer_unique_ptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Game
{
    private:
        std::vector<std::unique_ptr<Actor>> actors;
        unsigned long elapsed_milliseconds;
        bool running;
        sdl_window_unique_ptr window;
        sdl_renderer_unique_ptr renderer;
        Vector screen_size;
        void process_input();
        void update_world();
        void draw();         
    public:
        void run();
        Game(const unsigned short width, const unsigned short heigth);
        ~Game();
};