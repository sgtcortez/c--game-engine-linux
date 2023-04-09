#pragma once

#include <SDL2/SDL.h>
#include <string>

SDL_Texture * load_texture(std::string file_name, SDL_Renderer * renderer);
void unload(SDL_Texture* texture);

SDL_Window * create_window(
    const std::string title,
    const unsigned int width,
    const unsigned int heigth
);

SDL_Renderer * create_renderer(SDL_Window *window);