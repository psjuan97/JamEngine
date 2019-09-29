#include "AnimatedSprite.hpp"

#include <stdio.h>

 AnimatedSprite::AnimatedSprite(): clock() {
     actualAnimation = nullptr;
}

void AnimatedSprite::setAnimation(uint8_t id){

    actualAnimation = AssetManager::Instance()->getAnimation(id);
    this->Texture = actualAnimation->getTexture();

}


void AnimatedSprite::Draw(){
    if(actualAnimation != nullptr){
        if(clock.getElapsedTime().asMilliseconds()  >  actualAnimation->getDuration().asMilliseconds() ){
            slice = actualAnimation->getNextFrame(_indexClip);
            clock.restart();
        }

    Sprite::Draw();

    }
}
