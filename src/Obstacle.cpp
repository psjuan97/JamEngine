#include "Obstacle.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define SLOWMOTION_MULTIPLIER 0.1

Obstacle::Obstacle()
:alive(false), BaseSpeed(0), SpeedBoostPercentage(0)
{
    Direction = ObstaclesDirection::Top2Bottom;
}

Obstacle::Obstacle(const Obstacle& orig){
    ObstacleSprite = orig.ObstacleSprite;
}

Obstacle::~Obstacle(){
    
}

void Obstacle::setObstacleSpeed(int8_t X_Axis_Multiplier, int8_t Y_Axis_Multiplier, float _SPEED, float MAX){
    SPEED.x = X_Axis_Multiplier * _SPEED;
    SPEED.y = Y_Axis_Multiplier * _SPEED;

    BaseSpeed = _SPEED;
    SpeedBoostPercentage = (MAX-_SPEED)/_SPEED;
}


void Obstacle::FixedUpdate(float BoostTick){

    if(!alive) return;

    checkBounds();

    // float newSpeed = BaseSpeed - BaseSpeed*(BoostTick*SpeedBoostPercentage);

    // if(SPEED.x)
    //     SPEED.x = newSpeed;
    // else if(SPEED.y)
    //     SPEED.y = newSpeed;
    
    Position += SPEED;
}

void Obstacle::checkBounds(){
    math::Vector2f Size = ObstacleSprite.getSize();

    if(Direction == ObstaclesDirection::Top2Bottom && Position.y > SCREEN_HEIGHT){
        ObstacleSprite.Visibility = false;
        alive = false;
    }
    else if(Direction == ObstaclesDirection::Bottom2Top && (Position.y + Size.y < 0) ){
        ObstacleSprite.Visibility = false;
        alive = false;
    }
    else if(Direction == ObstaclesDirection::Left2Right && Position.x > SCREEN_WIDTH){
        ObstacleSprite.Visibility = false;
        alive = false;
    }
    else if(Direction == ObstaclesDirection::Right2Left && (Position.x + Size.x < 0)){
        ObstacleSprite.Visibility = false;
        alive = false;
    }
}

void Obstacle::Interpolate(float tick){

    float x = Previous.Position.x *(1-tick) + Current.Position.x*tick;
    float y = Previous.Position.y *(1-tick) + Current.Position.y*tick;
    

    if(SPEED.x != 0 || SPEED.y != 0)
        ObstacleSprite.setPosition(x, y);
}