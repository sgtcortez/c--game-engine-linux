#pragma once

#include "Component.hpp"
#include "Vector.hpp"

#include <SDL2/SDL_render.h>
#include <vector>
#include <string>
#include <memory>


enum State 
{
    ALIVE, /* Will be drawnable, respond to input and be updated*/
    DEAD,  /* Will be removed in the next game update */ 
    PAUSED /* Will not be drawnable, response to input and be updated. Wait for some action*/
};


class Actor
{
    protected:
        std::vector<std::shared_ptr<KeyboardComponent>> keyboard_components;
        std::vector<std::shared_ptr<UpdatableComponent>> updatable_components;
        std::vector<std::shared_ptr<DrawableComponent>> drawables_components;        
    public:
        const std::string name;
        Vector position;
        Vector velocity;
        float scale;
        float rotation;
        State state;
        void input(const unsigned char* keyboard_state);
        void update(const float delta_time);            
        void draw(SDL_Renderer *renderer);
        Actor(
            std::string name
        );

};