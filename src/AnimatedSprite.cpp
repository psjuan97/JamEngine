#include "AnimatedSprite.hpp"

#include <stdio.h>
void AnimatedSprite::setAnimation(uint8_t id){

    actualAnimation = AssetManager::Instance()->getAnimation(id);
    this->Texture = actualAnimation->getTexture();
}


void AnimatedSprite::Dro(){
    

    if(clock.getElapsedTime().asMilliseconds()  >  actualAnimation->getDuration().asMilliseconds() ){
        slice = actualAnimation->getNextFrame(_indexClip);
        clock.restart();
    }
    //printf("w: %i", slice->w);
    Sprite::Dro();

}
