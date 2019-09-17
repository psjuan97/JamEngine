#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Sprite{
    friend class JamEngine;
    // METHODS
    public:
        Sprite();
        Sprite(const Sprite& orig);
        void operator=(const Sprite &orig);
        ~Sprite();
        
        void setPosition(float x, float y);
        void setSize(float w, float h);

        inline glm::vec2 getPosition(){
            return glm::vec2(Size_Pos.x, Size_Pos.y);
        };

        inline glm::vec2 getSize(){
            return glm::vec2(Size_Pos.w, Size_Pos.h);
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