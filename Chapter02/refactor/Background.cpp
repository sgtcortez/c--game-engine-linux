#include "Background.hpp"
#include "SDL_Helper.hpp"

#include <iostream>

using namespace std;

BackgroundScrollableImage::BackgroundScrollableImage(SDL_Renderer* renderer, Vector screen_size)
:Actor("Background")
{

	position.x = screen_size.x / 2;
	position.y = screen_size.y / 2;
	
	scale = 1.0F;
	rotation = 0.0F;

	auto far_background = make_shared<BackgroundImageScrollableComponent>(BackgroundImageScrollableComponent(*this, screen_size, -100.0f));
    far_background->set_textures({
        load_texture("../Assets/Farback01.png", renderer),
        load_texture("../Assets/Farback02.png", renderer),
    });

    auto closer_background = make_shared<BackgroundImageScrollableComponent>(BackgroundImageScrollableComponent(*this, screen_size, -200.0f));
	closer_background->set_textures({
		load_texture("../Assets/Stars.png", renderer),
		load_texture("../Assets/Stars.png", renderer),
    });

    drawables_components.push_back(far_background);
	drawables_components.push_back(closer_background);
    updatable_components.push_back(far_background);
    updatable_components.push_back(closer_background);
}

BackgroundImageScrollableComponent::BackgroundImageScrollableComponent(
	BackgroundScrollableImage& owner,
	Vector screen_size,
	float scroll_speed
)
:owner(owner), BackgroundSpriteComponenet(screen_size, scroll_speed)
{}

void BackgroundImageScrollableComponent::process(SDL_Renderer *renderer)
{
    for (auto& background : textures)
    {
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(screenSize.x);
		r.h = static_cast<int>(screenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(owner.position.x - r.w / 2 + background.offset.x);
		r.y = static_cast<int>(owner.position.y - r.h / 2 + background.offset.y);

		// Draw this background
		SDL_RenderCopy(
			renderer,
			background.texture,
			nullptr,
			&r
		);        
    }
}

void BackgroundImageScrollableComponent::process(const float delta_time)
{
    for (auto& background : textures)
	{
		// Update the x offset
		background.offset.x += scrollSpeed * delta_time;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (background.offset.x < -screenSize.x)
		{
			background.offset.x = (textures.size() - 1) * screenSize.x - 1;
		}
	}
}
