#pragma once 

#include "Sprite.hpp"
#include "AssetManager.hpp"
#include "eClock.hpp"
#include <string>


//Animation walk = Animation("heroWalk.png", 7, eTime(1), true );


/////////////////////////////////////////////////////
////
////
/////////////////////////////////////////////////////

class AnimatedSprite : public Sprite {
    
    private:
        Animation* actualAnimation;
        int _indexClip = 0;
        eClock clock;
    public:
        AnimatedSprite();
        void setAnimation(uint8_t id);
        void Draw();



};