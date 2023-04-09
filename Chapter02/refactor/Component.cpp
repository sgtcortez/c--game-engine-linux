#include "Component.hpp"

using namespace std;


void SpriteComponent::set_texture(SDL_Texture *texture)
{
    this->texture = texture;
    // Set width/height
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &heigth);            
}

SDL_Texture * SpriteComponent::get_texture() const 
{
    return texture;
}

const int SpriteComponent::get_width() const 
{
    return width;
}

const int SpriteComponent::get_heigth() const
{
    return heigth;
}

void AnimatedSpriteComponent::set_textures(std::vector<SDL_Texture *> textures)
{
    this->textures = textures;
    
    // Set the active texture to first frame
    currentFrameDisplayed = 0.0F;
    SpriteComponent::set_texture(this->textures[0]);
}

const std::vector<SDL_Texture *> AnimatedSpriteComponent::get_textures() const
{
    return textures;
}

BackgroundSpriteComponenet::BackgroundSpriteComponenet(Vector screen_size, float scroll_speed)
{
    this->screenSize = screen_size;
    this->scrollSpeed = scroll_speed;
}


void BackgroundSpriteComponenet::set_textures(const std::vector<SDL_Texture *> textures)
{
    this->textures.clear();
    for (int index = 0; index < textures.size(); index++)
    {   
        BGTexture temp;
        temp.texture = textures[index];
        // Each texture is screen width in offset
        temp.offset.x = index * screenSize.x;
        temp.offset.y = 0;

        /*
         Altrought the author uses emplace_back method to insert the elment in the list, it is not
         necessary and just adds complexity to the code 
         so push back is more convenient in this case

         vector::push_back https://cplusplus.com/reference/vector/vector/push_back/
         vector::emplace_back https://cplusplus.com/reference/vector/vector/emplace_back/

         a good explanation https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back
         this->textures.emplace_back(temp); 
        */
        this->textures.push_back(temp);
    }
}