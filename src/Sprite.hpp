#ifndef SPRITE_H
#define SPRITE_H

#include "math/Vector2.hpp"
#include <vector>

#include <SDL2/SDL.h>
#include "JamEngine.hpp"
class Sprite{
    // METHODS
    public:
        friend class JamEngine;
        Sprite();
        Sprite(const Sprite& orig);
        void operator=(const Sprite &orig);
        ~Sprite();
        
        void setPosition(float x, float y);
        void setSize(float w, float h);

        inline math::Vector2<float> getPosition(){
            return math::Vector2<float>(Size_Pos.x, Size_Pos.y);
        };

        inline math::Vector2<float> getSize(){
            return math::Vector2<float>(Size_Pos.w, Size_Pos.h);
        };

        inline void setTexture(SDL_Texture* T){
            Texture = T;
        };

        void Dro();

    private:
        static inline void setRenderer(SDL_Renderer* R){
            Renderer = R;
        };

    // VARIABLES
    public:
    
    private:
        static SDL_Renderer* Renderer;

        SDL_Texture* Texture;
        SDL_Rect Size_Pos;
};

#endif