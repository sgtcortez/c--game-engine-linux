#pragma once

#include "Actor.hpp"
#include "Component.hpp"

class BackgroundScrollableImage : public Actor
{
    public:
        BackgroundScrollableImage(SDL_Renderer *renderer, Vector screen_size);
};

struct BackgroundImageScrollableComponent : public BackgroundSpriteComponenet
{   
    private:
        BackgroundScrollableImage& owner;
    public:
        BackgroundImageScrollableComponent(BackgroundScrollableImage& owner, Vector screen_size, float scroll_speed);
    void process(SDL_Renderer *renderer) override;
    void process(const float delta_Time) override;
};

