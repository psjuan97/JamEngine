#ifndef ZONE_H
#define ZONE_H

#include "engineModules/Sprite.hpp"
#include "engineModules/eClock.hpp"

#include "Obstacle.hpp"
#include <cstdint>
#include <vector>
#include <array>
#include "PopUp.hpp"


#include "enumObstacleDir.hpp"

class sGame;

class Zone{
    // METHODS
    public:
        Zone();
        Zone(const Zone& orig) = delete;
        ~Zone();


        void setAlertTargetInstance(sGame* Target);
        void setZoneBackground(SDL_Texture* Texture, float x, float y, float w, float h);
        void setZoneTime(uint16_t Seconds);
        
        
        //    From                                  To  
        //      |                                   |
        //      |  x  |  x  |  x  |  x  |  x  |  x  |   // 6 Divisions
        void setSpawnAreaAndDivisions(float From, float To, float Aux, uint8_t Divisions);
                                                            // Aux será X o Y en función de la dirección de los obstáculos


        void setObstaclesDirection(ObstaclesDirection Dir);
        void setObstaclesSize(float W, float H);
        void setObstacleInitialAndMaxVelocity(float Initial, float MAX);
       // void setObstaclesTexture(SDL_Texture* Texture);
        void setObstaclesAnim(uint8_t animid);

        void setZIndex(uint8_t Z);

        ObstaclesDirection getObstacleDirection();

        void setSpawnRate(float Seconds);


        void checkPlayerCollisions(math::Vector2f PlayerPosition, math::Vector2f PlayerSize);
        void FixedUpdate();
        void InterpolateObstacles(float Tick);
        void setSlowDown();
        void CleanZone();
        void resetClock();
        inline void enableDisableBackground(bool flag){
            Background.Visibility = flag;
        };

    private:
        void Countdown();
        void SpawnHandler();
        void ObstaclesUpdate();

    // VARIABLES
    private:

        std::vector<float> OBSTACLES_SPAWNPOINTS;
        std::array<Obstacle, 20> OBSTACLES;

        eClock ZoneTimer;
        
        Sprite Background;

        float ObstaclesSpeed;
        float XY_Aux;

        float Accumulator;
        float SpawnRate;

        math::Vector2f ObstacleSize;
        //SDL_Texture* oTexture;
        uint8_t obstacleAnimID;
        sGame* ALERT_TARGET;

        ObstaclesDirection Direction;
        uint8_t ObstaclesIterator;

        //Para las colisiones
        //math::Vector2f* PlayerPosition;
};

#endif