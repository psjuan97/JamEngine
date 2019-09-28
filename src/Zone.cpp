#include "Zone.hpp"
#include <string>


Zone::Zone()
:ZONE_TIME_seconds(0), ObstaclesSpeed(0), SpawnFrom(0), SpawnTo(0), XY_Aux(0), ZoneElapsedTime(0), 
 Accumulator(0), SpawnRate(1), ObstaclesIterator(0), COUNTDOWN(40, 100)
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
        JAM->setDrawable_ZIndex(&OBSTACLES[i], Z);
    }
}



void Zone::setZoneTime(uint16_t Seconds){
    ZONE_TIME_seconds = Seconds;
    ZoneTimer.restart();
}

void Zone::setSpawnArea(float From, float To, float Aux){
    SpawnFrom = From;
    SpawnTo = To;
    XY_Aux = Aux;
}

void Zone::setSpawnRate(float Seconds){
    SpawnRate = Seconds;
}


void Zone::setSpawnAreaDivisions(uint8_t Divisions){
    OBSTACLES_SPAWNPOINTS.clear();
    float DivisibleArea = SpawnTo - SpawnFrom;

    float BlockSize = DivisibleArea/Divisions;
    float BlockMiddlePoint = BlockSize/2;

    // Punto medio teniendo en cuenta el ancho del obstáculo
    float MiddlePoint = 0;
    if(Direction == Top2Bottom || Direction == Bottom2Top){
        MiddlePoint = BlockMiddlePoint - ObstacleSize.x/2;
    }
    else{
        MiddlePoint = BlockMiddlePoint - ObstacleSize.y/2;
    }
    
    MiddlePoint += SpawnFrom;

    for(uint8_t i = 0; i < Divisions; ++i){
        OBSTACLES_SPAWNPOINTS.emplace_back(MiddlePoint);
        MiddlePoint += BlockSize;
    }
}


void Zone::setObstaclesDirection(ObstaclesDirection Dir){
    Direction = Dir;
}


void Zone::setObstaclesSize(float W, float H){
    ObstacleSize.x = W;
    ObstacleSize.y = H;
}

void Zone::setObstaclesTexture(SDL_Texture* Texture){
    oTexture = Texture;
}

void Zone::Update(){

    float dt = ZoneTimer.restart().asSeconds();
    ZoneElapsedTime += dt;
    Accumulator += dt;

    Countdown();
    SpawnHandler();
    

    for(uint8_t i = 0; i < OBSTACLES.size(); ++i){
        if(Direction == ObstaclesDirection::Top2Bottom)
            OBSTACLES[i].setY(OBSTACLES[i].getPosition().y + 2);
        if(Direction == ObstaclesDirection::Bottom2Top)
            OBSTACLES[i].setY(OBSTACLES[i].getPosition().y - 2);
    }
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

        Sprite& Target = OBSTACLES[ObstaclesIterator];

        int randon = rand() % (OBSTACLES_SPAWNPOINTS.size());
        float COORD = OBSTACLES_SPAWNPOINTS[randon];

        if(Direction == Top2Bottom || Direction == Bottom2Top){
            Target.setPosition( COORD , XY_Aux);
        }
        else{
            Target.setPosition( XY_Aux, COORD);
        }

        Target.setSize(ObstacleSize.x, ObstacleSize.y);
        Target.setTexture(oTexture);
        ++ObstaclesIterator;
        if(ObstaclesIterator >= OBSTACLES.size()) 
            ObstaclesIterator = 0;
    }
}
