#include "Animation.hpp"
#include "AssetManager.hpp"

Animation::Animation( uint8_t textureID, int nframes, eTime const& duration, bool looping)
    :  _duration(duration), _loop (looping){

            this->texture = AssetManager::Instance()->getTexture(textureID);

            if (this->texture == nullptr) {
                std::cout << "##################### ANIMATIONTEXTURA ES NULLPTR" << std::endl;
            }

            int w;
            SDL_Rect rect; 
            SDL_QueryTexture(texture, NULL, NULL, &w, &rect.h);
            rect.x = 0;
            rect.y = 0;
            rect.w = w/nframes;
            
            
            for (unsigned int i = 0; i < nframes; i++)
            {
                _frames.push_back(rect);
                rect.x += w/nframes;
            }
 }