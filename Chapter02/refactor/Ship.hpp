#pragma once

#include "Actor.hpp"
#include "Component.hpp"
#include "Vector.hpp"

class Ship : public Actor
{
    public:
        Ship(SDL_Renderer * renderer);
};

struct ShipKeyboardComponent : public KeyboardComponent
{
    private:
        Ship& owner;
    public:
        ShipKeyboardComponent(Ship& owner);
        void process(const unsigned char *keyboard_state) override;
};

struct ShipUpdatableComponent : public UpdatableComponent
{
    private:
        Ship& owner;
    public:
        ShipUpdatableComponent(Ship& owner);
        void process(const float delta_time) override;
};

struct ShipDrawableComponent : public AnimatedSpriteComponent
{
    private:
        Ship& owner;
    public:
        ShipDrawableComponent(Ship& owner);
        void process(SDL_Renderer *renderer) override;
        void process(const float delta_Time) override;
};



