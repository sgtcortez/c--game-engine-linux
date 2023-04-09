#include "Ship.hpp"
#include "Actor.hpp"
#include "Component.hpp"
#include "SDL_Helper.hpp"
#include "Math.hpp"

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

using namespace std;

constexpr static int IMAGES_PER_SECOND = 24;


Ship::Ship(SDL_Renderer * renderer)
:Actor("Ship")
{
    position = {100, 384};
    velocity = {0, 0};
	scale = 1.5F;
	rotation = 0.0F;

	keyboard_components.push_back(make_shared<ShipKeyboardComponent>(ShipKeyboardComponent(*this)));
	updatable_components.push_back(make_shared<ShipUpdatableComponent>(ShipUpdatableComponent(*this)));
	
	/**
	 * Since this one is an animated sprint, it must be updated using the delta time value
	*/
	auto drawableComponent = make_shared<ShipDrawableComponent>(ShipDrawableComponent(*this));
	drawableComponent->set_textures({
		load_texture("../Assets/Ship01.png", renderer),
		load_texture("../Assets/Ship02.png", renderer),
		load_texture("../Assets/Ship03.png", renderer),
		load_texture("../Assets/Ship04.png", renderer)
	});

	drawableComponent->currentFrameDisplayed = 0.0F;
	drawableComponent->animationFrameRate = IMAGES_PER_SECOND;

	drawables_components.push_back(drawableComponent);
	updatable_components.push_back(drawableComponent);
}


ShipKeyboardComponent::ShipKeyboardComponent(Ship& owner)
:owner(owner)
{}

ShipUpdatableComponent::ShipUpdatableComponent(Ship& owner)
:owner(owner)
{}

ShipDrawableComponent::ShipDrawableComponent(Ship& owner)
:owner(owner)
{
	animationFrameRate = IMAGES_PER_SECOND;
}

void ShipKeyboardComponent::process(const unsigned char *keyboard_state)
{

	// Reset previous key pressed
	owner.velocity.x = 0;
	owner.velocity.y = 0;

	// right/left
	if (keyboard_state[SDL_SCANCODE_D])
	{
		owner.velocity.x += 250.0f;
	}
	if (keyboard_state[SDL_SCANCODE_A])
	{
		owner.velocity.x -= 250.0f;
	}
	// up/down
	if (keyboard_state[SDL_SCANCODE_S])
	{
		owner.velocity.y += 300.0f;
	}
	if (keyboard_state[SDL_SCANCODE_W])
	{
		owner.velocity.y -= 300.0f;
	}
}



void ShipUpdatableComponent::process(const float delta_time) 
{
	// Update position based on speeds and delta time
	owner.position.x += owner.velocity.x * delta_time;
	owner.position.y += owner.velocity.y * delta_time;
	
	// Restrict position to left half of screen
	if (owner.position.x < 25.0f)
	{
		owner.position.x = 25.0f;
	}
	else if (owner.position.x > 500.0f)
	{
		owner.position.x = 500.0f;
	}
	if (owner.position.y < 25.0f)
	{
		owner.position.y = 25.0f;
	}
	else if (owner.position.y > 743.0f)
	{
		owner.position.y = 743.0f;
	}    
}


void ShipDrawableComponent::process(SDL_Renderer *renderer)
{
	SDL_Texture* current_texture = SpriteComponent::get_texture();

	// This object is allocated on stack, so, its free after this stack frame
	// goes out of scope
	SDL_Rect rect;

	// Scale the width/height by owner's scale
	rect.w = static_cast<int>(SpriteComponent::get_width() * owner.scale);
	rect.h = static_cast<int>(SpriteComponent::get_heigth() * owner.scale);
	// Center the rectangle around the position of the owner
	rect.x = static_cast<int>(owner.position.x - rect.w / 2);
	rect.y = static_cast<int>(owner.position.y - rect.h / 2);

	SDL_RenderCopyEx(
		renderer,
		current_texture,
		nullptr,
		&rect,
		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		Math::negate(Math::to_degress(owner.rotation)),
		nullptr,
		SDL_FLIP_NONE
	);
    
}

void ShipDrawableComponent::process(const float delta_time)
{
	// update the current frame based on frame rate and delta time
	currentFrameDisplayed += animationFrameRate * delta_time;

	const vector<SDL_Texture *> current_textures = AnimatedSpriteComponent::get_textures();

	// Wrap current frame. I really dont know why this ...
	while (currentFrameDisplayed >= current_textures.size())
	{
		currentFrameDisplayed -= current_textures.size();
	}

	// Set the texture to be rendered
	SDL_Texture* to_display = current_textures[static_cast<int>(currentFrameDisplayed)];

	// Call the parent class(Sprite) to set the texture
	SpriteComponent::set_texture(to_display);
}
