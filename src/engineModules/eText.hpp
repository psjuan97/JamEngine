#pragma once 

#include <string>
#include <SDL2/SDL_ttf.h>

#include "eFont.hpp"

class eText{
    public: 
        friend class JamEngine;
        static void setFont(eFont* font);
        eText(int x,int y);
        ~eText();
        void draw();
        void setPosition(int x,int y);
        void setString(std::string str);
    private:

    static inline void setRenderer(SDL_Renderer* R){
        Renderer = R;
    };


        
    private:
        int posX, posY;
        SDL_Texture* texture;
        static eFont* font;
        static SDL_Renderer* Renderer;

};
