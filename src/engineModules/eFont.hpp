
#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>


/////////
///     TODO
///  liberar la fuente en el destructor
class eFont{
    public:
        eFont(const char* str, int size);
        ~eFont();

        inline TTF_Font* getSDLFont() const {
            return sdl_font;
        };
        
    private:
        TTF_Font* sdl_font = nullptr;

};