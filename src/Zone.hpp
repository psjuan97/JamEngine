#ifndef ZONE_H
#define ZONE_H

#include "engineModules/Sprite.hpp"
#include "engineModules/eClock.hpp"
#include "Obstacle.hpp"
#include <cstdint>
#include <vector>
#include <array>

#include "enumObstacleDir.hpp"



class Zone{
    // METHODS
    public:
        Zone();
        Zone(const Zone& orig) = delete;
        ~Zone();


        

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
        void setObstaclesTexture(SDL_Texture* Texture);
        void setZIndex(uint8_t Z);

        ObstaclesDirection getObstacleDirection();

        void setSpawnRate(float Seconds);

        void FixedUpdate();
        void InterpolateObstacles(float Tick);
        void setSlowDown();
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
        eText COUNTDOWN;

        uint16_t ZONE_TIME_seconds;
        uint16_t ZONE_LAST_TIME = 0;


        float ObstaclesSpeed;
        float XY_Aux;

        bool END;
        float ZoneElapsedTime;
        float Accumulator;
        float SpawnRate;

        math::Vector2f ObstacleSize;
        SDL_Texture* oTexture;

        ObstaclesDirection Direction;
        uint8_t ObstaclesIterator;


        //Para las colisiones
        //math::Vector2f* PlayerPosition;
};

#endif