#include "SDL_Helper.hpp"

#include <unordered_map>
#include <string>
#include <SDL2/SDL_image.h>

#ifdef DEBUG
    #include <iostream>
    #include "debug_helper.hpp"
#endif

using namespace std;

// TODO: Maybe we can use smart pointers like shared pointers to do this sort of stuff ...
// https://en.cppreference.com/w/cpp/memory/shared_ptr
struct ReferenceCounting
{
    SDL_Texture *texture;

    // When this one reaches 0, we can free this texture
    unsigned int references;
};

// This game is not multithreaded, so, there is no need to add complexity and make 
// this map thread safe ...
unordered_map<string, ReferenceCounting> cached_textures;

SDL_Texture * load_texture(string file_name, SDL_Renderer * renderer)
{
    
    auto iterator = cached_textures.find(file_name); 

    if (iterator != cached_textures.end())
    {
        // found from cache, no, we just need to increment the reference counter and return the texture
        // uses reference(&) to ask the iterator to return an reference of the value instead of just a copy
        // first -> Key, second -> value
        ReferenceCounting& value = iterator->second;
        value.references++;
#ifdef DEBUG
        INFO << "Found data in cache from filename: " << file_name << " References: " << to_string(value.references) << endl;
#endif  
        return value.texture;
    } 
    // The image do not exists in our local cache, so we must load from the operating system 

    SDL_Surface *surface = IMG_Load(file_name.c_str());
    if (!surface)
    {
        throw "Could not load the image!";
    }
    SDL_Texture *loaded = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!loaded)
    {
        throw "Could not convert surface to texture!";
    }

    ReferenceCounting value;
    value.texture = loaded;
    value.references = 1;
    
    cached_textures[file_name] = value;

#ifdef DEBUG
    INFO << "New file loaded to cache. Filename: " << file_name << endl;
#endif  

    return loaded;
}

void unload(string file_name)
{
    auto iterator = cached_textures.find(file_name); 

    if (iterator == cached_textures.end())
    {
        // Not found in the cache, just ignores
        return;
    }

    // Use references here, so we do not need to update the map after 
    // updating the value
    ReferenceCounting& value = iterator->second;
    value.references--;

#ifdef DEBUG
    INFO << "Decreased references to filename:: " << file_name << " References: " << to_string(value.references) << endl;
#endif  

    if (value.references == 0)
    {
        SDL_DestroyTexture(value.texture);
        // after reaching 0 references we must remove from the map too
        cached_textures.erase(iterator);

#ifdef DEBUG
        INFO << "Unloaded filename: " << file_name << endl;
#endif  
    }
}

SDL_Window * create_window(
    const std::string title,
    const unsigned int width,
    const unsigned int heigth
)
{
	SDL_Window* window = SDL_CreateWindow(
        "Game Programming in C++ (Chapter 2) Refactored", 
        100, 
        100, 
        width, 
        heigth,
        0
    );
    if (window == nullptr)
    {
        throw "Could not create Window ...";
    }
    return window;
}


SDL_Renderer * create_renderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );    
    if (renderer == nullptr)
    {
        throw "Could not create renderer from window!";
    }
    return renderer;
}