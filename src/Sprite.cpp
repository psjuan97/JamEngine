#include "Sprite.hpp"

SDL_Renderer* Sprite::Renderer = nullptr;

Sprite::Sprite()
:Texture(nullptr)
{
    Size_Pos.h = 0;
    Size_Pos.w = 0;
    Size_Pos.x = 0;
    Size_Pos.y = 0;

    slice = &Size_Pos;

}

Sprite::Sprite(const Sprite& orig){
    Texture = orig.Texture;
    Size_Pos = orig.Size_Pos;
}

void Sprite::operator=(const Sprite& orig){
    Texture = orig.Texture;
    Size_Pos = orig.Size_Pos;
}

Sprite::~Sprite(){

}

void Sprite::setPosition(float x, float y){
    Size_Pos.x = x;
    Size_Pos.y = y;
}

void Sprite::setSize(float w, float h){
    Size_Pos.w = w;
    Size_Pos.h = h;
}

void Sprite::Dro(){
    JamEngine::Instance()->drawTexture(Texture, slice, &Size_Pos);

}