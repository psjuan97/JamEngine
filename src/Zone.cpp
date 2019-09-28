#include "Zone.hpp"
#include <string>


Zone::Zone()
:ZONE_TIME_seconds(0), ObstaclesSpeed(0), XY_Aux(0), ZoneElapsedTime(0), 
 Accumulator(0), SpawnRate(1), ObstaclesIterator(0), COUNTDOWN(230, 0), END(false)
{
    ObstacleSize.x = 15;
    ObstacleSize.y = 15;

    OBSTACLES_SPAWNPOINTS.reserve(10);
	COUNTDOWN.setString("00");
    JamEngine::Instance()->setDrawable_ZIndex(&COUNTDOWN, 2);
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

void Zone::setZoneTime(uint16_t Seconds){
    ZONE_TIME_seconds = Seconds;
    ZoneTimer.restart();
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

void Zone::setObstaclesTexture(SDL_Texture* Texture){
    oTexture = Texture;
}

void Zone::setObstacleInitialAndMaxVelocity(float Initial, float MAX){

    int8_t X_AXIS = 0;
    int8_t Y_AXIS = 0;
    if(Direction == ObstaclesDirection::Top2Bottom){
        Y_AXIS = 1;
    }
    else if(Direction == ObstaclesDirection::Bottom2Top){
        Y_AXIS = -1;
    }
    else if(Direction == ObstaclesDirection::Left2Right){
        X_AXIS = 1;
    }
    else{
        X_AXIS = -1;
    }

    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].setObstacleSpeed(X_AXIS, Y_AXIS, Initial, MAX);
    }
}


void Zone::FixedUpdate(){

    if(END) return;

    float dt = ZoneTimer.restart().asSeconds();
    ZoneElapsedTime += dt;
    Accumulator += dt;

    if(ZoneElapsedTime > ZONE_TIME_seconds)
        END = true;

    int CD = ZONE_TIME_seconds-ZoneElapsedTime;

    if(CD != ZONE_LAST_TIME){
        Countdown();
        ZONE_LAST_TIME  = CD;
    }
    SpawnHandler();
    ObstaclesUpdate();

}

void Zone::Countdown(){
    int CD = ZONE_TIME_seconds-ZoneElapsedTime;
    std::string Countdown = to_string(CD);
    
    if(CD < 10)
        Countdown = "0"+Countdown;
  

	COUNTDOWN.setString(Countdown);
}

void Zone::SpawnHandler(){
    if(Accumulator > SpawnRate){
        Accumulator -= SpawnRate;

        Obstacle& Target = OBSTACLES[ObstaclesIterator];
        Target.alive = true;
        Target.ObstacleSprite.Visibility = true;

        int random = rand() % (OBSTACLES_SPAWNPOINTS.size());
        float COORD = OBSTACLES_SPAWNPOINTS[random];

        if(Direction == Top2Bottom || Direction == Bottom2Top){
            Target.Position = math::Vector2f(COORD , XY_Aux);
        }
        else{
            // std::cout << "random [" << random << "] " << XY_Aux << ", " << COORD << std::endl;
            Target.Position = math::Vector2f(XY_Aux, COORD);
        }
        
        Target.saveCurrentState();
        Target.savePreviousState();

        Target.ObstacleSprite.setSize(ObstacleSize.x, ObstacleSize.y);
        Target.ObstacleSprite.setTexture(oTexture);
        ++ObstaclesIterator;
        if(ObstaclesIterator >= OBSTACLES.size()) 
            ObstaclesIterator = 0;
    }
}

void Zone::ObstaclesUpdate(){
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].savePreviousState();

        OBSTACLES[i].FixedUpdate(ZoneElapsedTime/ZONE_TIME_seconds);
        
        OBSTACLES[i].saveCurrentState();
    }
}

void Zone::InterpolateObstacles(float Tick){
    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        OBSTACLES[i].Interpolate(Tick);
    }
}


ObstaclesDirection setObstaclesDirection(ObstaclesDirection Dir) {
    return Dir;
}

ObstaclesDirection Zone::getObstacleDirection() {
    return OBSTACLES[0].Direction;
}