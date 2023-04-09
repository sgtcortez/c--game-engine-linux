#include "Actor.hpp"
#include "Component.hpp"

#include <vector>

using namespace std;

Actor::Actor(
    string name
):name(name)
{
    state = ALIVE;
};


void Actor::input(const unsigned char *keyboard_state)
{
    for (auto& component : keyboard_components)
    {
        component->process(keyboard_state);
    }
}

void Actor::update(const float delta_time)
{
    for (auto& component : updatable_components)
    {
        component->process(delta_time);
    }
}

void Actor::draw(SDL_Renderer *renderer)
{
    for (auto& component : drawables_components)
    {
        component->process(renderer);
    }
}