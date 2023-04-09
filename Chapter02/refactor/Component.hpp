#pragma once

#include <vector>
#include <SDL2/SDL_render.h>

#include "Vector.hpp"

/**
 * This struct represents an input of the keyboard.  
 * For example, if we have an actor that moves in the screen, and our player control to where he will move
 * This method(process) will be called after we received the keyboard state from SDL. 
 * Function: https://wiki.libsdl.org/SDL2/SDL_GetKeyboardState
*/
struct KeyboardComponent
{
    virtual void process(const unsigned char *keyboard_state) = 0;
};

/**
 * This struct represents something that must be updated by the delta time
 * For example, an actor that moves in the screen if no key was pressed
*/
struct UpdatableComponent
{
    virtual void process(const float delta_time) = 0;
};

/**
 * This struct represents an componenet that must be draw using the renderer
*/
struct DrawableComponent
{
    virtual void process(SDL_Renderer *renderer) = 0;
};

struct SpriteComponent : public DrawableComponent
{
    private:
        SDL_Texture* texture;
        int width;
        int heigth;
    public:
        void set_texture(SDL_Texture *texture);
        SDL_Texture * get_texture() const;
        const int get_width() const;
        const int get_heigth() const;
};

struct AnimatedSpriteComponent : public SpriteComponent, public UpdatableComponent
{
    private:
        std::vector<SDL_Texture *> textures;
    public:
        float currentFrameDisplayed;
        float animationFrameRate;    
        void set_textures(std::vector<SDL_Texture *> textures);
        const std::vector<SDL_Texture *> get_textures() const;
};

struct BackgroundSpriteComponenet : public SpriteComponent, UpdatableComponent
{

    BackgroundSpriteComponenet(Vector screen_size, float scroll_speed);

	// Struct to encapsulate each background image and its offset
	struct BGTexture
	{
		SDL_Texture* texture;
		Vector offset;
	};
	std::vector<BGTexture> textures;
	Vector screenSize;
	float scrollSpeed;

    void set_textures(const std::vector<SDL_Texture *> textures);
};

