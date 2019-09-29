#include "Zone.hpp"
#include <string>
#include "ASSETS_IDs.hpp"
#include "sGame.hpp"
#include "engineModules/StateMachine.hpp"
#include "engineModules/EventManager.hpp"
#include "sScore.hpp"


Zone::Zone()
:ObstaclesSpeed(0), XY_Aux(0), 
 Accumulator(0), SpawnRate(1), ObstaclesIterator(0), obstacleAnimID(0)
{
    ObstacleSize.x = 15;
    ObstacleSize.y = 15;

    OBSTACLES_SPAWNPOINTS.reserve(10);
}

Zone::~Zone(){

}

void Zone::setZoneBackground(SDL_Texture* Texture, float x, float y, float w, float h){
    
    Background.setTexture(Texture);
    Background.setPosition(x, y);
    Background.setSize(w, h);

	JamEngine::Instance()->setDrawable_ZIndex(&Background, 0);
}

void Zone::setZIndex(uint8_t Z){
    JamEngine* JAM = JamEngine::Instance();

    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        JAM->setDrawable_ZIndex(&OBSTACLES[i].ObstacleSprite, Z);
    }
}

void Zone::setSpawnAreaAndDivisions(float From, float To, float Aux, uint8_t Divisions){

    XY_Aux = Aux;

    OBSTACLES_SPAWNPOINTS.clear();

    // From                                  To  
    //   |     <------ Distance ------->     |
    float DivisibleArea = To - From;

    //   |=====|     |     |     |     |     |
    float BlockSize = DivisibleArea/Divisions;

    //   |==x==|     |     |     |     |     |
    float BlockMiddlePoint = BlockSize/2;

    // Punto medio teniendo en cuenta el ancho del obstáculo
    float MiddlePoint = 0;
    if(Direction == Top2Bottom || Direction == Bottom2Top){
        MiddlePoint = BlockMiddlePoint - ObstacleSize.x/2;
    }
    else{
        MiddlePoint = BlockMiddlePoint - ObstacleSize.y/2;
    }
    
    MiddlePoint += From;

    for(uint8_t i = 0; i < Divisions; ++i){
        OBSTACLES_SPAWNPOINTS.emplace_back(MiddlePoint);
        MiddlePoint += BlockSize;
    }
}

void Zone::setSpawnRate(float Seconds){
    SpawnRate = Seconds;
}


void Zone::setObstaclesDirection(ObstaclesDirection Dir){
    Direction = Dir;
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].Direction = Dir;
    }
}

void Zone::setObstaclesSize(float W, float H){
    ObstacleSize.x = W;
    ObstacleSize.y = H;
}

/*
void Zone::setObstaclesTexture(SDL_Texture* Texture){
    oTexture = Texture;
    
}obstacleAnimID
*/

void Zone::setObstaclesAnim(uint8_t anim){
    obstacleAnimID = anim;
}


void Zone::setObstacleInitialAndMaxVelocity(float Initial, float MAX){

    int8_t X_AXIS = 0;
    int8_t Y_AXIS = 0;
    if(Direction == ObstaclesDirection::Top2Bottom){
        Y_AXIS = 1;
    }
    else if(Direction == ObstaclesDirection::Bottom2Top){
        Y_AXIS = -1;
        MAX = -MAX;
    }
    else if(Direction == ObstaclesDirection::Left2Right){
        X_AXIS = 1;
    }
    else{
        X_AXIS = -1;
        MAX = -MAX;
    }

    math::Vector2f Speed(X_AXIS*Initial, Y_AXIS*Initial);

    // std::cout << "SPEED " << Speed.x << ", " << Speed.y << std::endl;
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i) {
        OBSTACLES[i].setObstacleSpeed(Speed, MAX);
    }
}


void Zone::FixedUpdate(){

    float dt = ZoneTimer.restart().asSeconds();

    Accumulator += dt;

    SpawnHandler();
    ObstaclesUpdate();
}

#include <iostream>

void Zone::SpawnHandler(){

    if(Accumulator > SpawnRate){
        Accumulator -= SpawnRate;
        Obstacle& Target = OBSTACLES[ObstaclesIterator];
        Target.alive = true;
        Target.ObstacleSprite.Visibility = true;

        int random = rand() % OBSTACLES_SPAWNPOINTS.size();
        float COORD = OBSTACLES_SPAWNPOINTS[random];

        if(Direction == Top2Bottom || Direction == Bottom2Top){
            // std::cout << "random [" << random << "] " << COORD << ", " << XY_Aux << std::endl;
            Target.Position = math::Vector2f(COORD , XY_Aux);
        }
        else{
            Target.Position = math::Vector2f(XY_Aux, COORD);
        }
        
        Target.saveCurrentState();
        Target.savePreviousState();

        Target.ObstacleSprite.setSize(ObstacleSize.x, ObstacleSize.y);
        //Target.ObstacleSprite.setTexture(oTexture);
        Target.ObstacleSprite.setAnimation(this->obstacleAnimID);

        ++ObstaclesIterator;
        if(ObstaclesIterator >= OBSTACLES.size()) 
            ObstaclesIterator = 0;
    }
}

void Zone::ObstaclesUpdate(){
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].savePreviousState();

        OBSTACLES[i].FixedUpdate(0);
        
        OBSTACLES[i].saveCurrentState();
    }
}

void Zone::InterpolateObstacles(float Tick){
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].Interpolate(Tick);
    }
}


void Zone::setAlertTargetInstance(sGame* Target){
    ALERT_TARGET = Target;
}

ObstaclesDirection Zone::getObstacleDirection() {
    return OBSTACLES[0].Direction;
}


#define PLAYER_WIDTH 8

void Zone::checkPlayerCollisions(math::Vector2f PlayerPosition, math::Vector2f PlayerSize){
    
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        Obstacle& CurrentObstacle = OBSTACLES[i];
        math::Vector2f ObstaclePostion = CurrentObstacle.Position;
        math::Vector2f ObstacleSize = CurrentObstacle.ObstacleSprite.getSize();

        if( PlayerPosition.x < ObstaclePostion.x + ObstacleSize.x &&
            PlayerPosition.x + PlayerSize.x > ObstaclePostion.x &&
            PlayerPosition.y < ObstaclePostion.y + ObstacleSize.y &&
            PlayerPosition.y + PlayerSize.y > ObstaclePostion.y
          ) {
              CurrentObstacle.alive = false;
              CurrentObstacle.ObstacleSprite.Visibility = false;

                EventManager::Instance()->resetKeys();
                StateMachine::Instance()->setState(new sScore);

            }
    }
}
void Zone::CleanZone() {
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].alive = false;
        OBSTACLES[i].ObstacleSprite.Visibility = false;
    }
}

void Zone::resetClock(){
    ZoneTimer.restart();
}
