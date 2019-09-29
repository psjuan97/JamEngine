#pragma once

#include "eTime.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
class Animation {
public:
    std::vector<SDL_Rect> _frames;
    SDL_Texture* texture;
    eTime _duration;
    bool _loop;

public:
    Animation( uint8_t textureID, int nframes,
        eTime const& duration, bool looping);


    inline eTime getDuration(){
        return _duration;
    }

    inline SDL_Rect* getNextFrame(int &actual){

        ++actual;
        if(_frames.size() <= actual  ){
            actual = 0;
        }

        return &_frames[actual];
    }

    inline SDL_Texture* getTexture(){
        return texture;
    }
};
