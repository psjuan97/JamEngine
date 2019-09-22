#include "eFont.hpp"
#include <stdio.h>

eFont::eFont(const char* file, int size = 35){
        sdl_font = TTF_OpenFont(file, size); 
        if(sdl_font == nullptr){
            printf("TTF_OPEN FONT: %s\n", TTF_GetError());
        }
}

eFont::~eFont(){
    TTF_CloseFont(sdl_font);
    sdl_font = nullptr;
}