#ifndef ZONE_H
#define ZONE_H

#include "engineModules/Sprite.hpp"
#include "engineModules/eClock.hpp"
#include <cstdint>
#include <vector>
#include <array>

enum ObstaclesDirection{
    Top2Bottom = 0,
    Bottom2Top,
    Left2Right,
    Right2Left
};

class Zone{
    // METHODS
    public:
        Zone();
        Zone(const Zone& orig) = delete;
        ~Zone();


        void setZoneBackground(SDL_Texture* Texture, float x, float y, float w, float h);
        void setZoneTime(uint16_t Seconds);
        
        
        void setSpawnArea(float From, float To, float Aux);
        //    From                                  To  // Aux será X o Y en función de la dirección de los obstáculos
        //      |                                   |
        //      |  x  |  x  |  x  |  x  |  x  |  x  |   // 6 Divisions
        void setSpawnAreaDivisions(uint8_t Divisions);


        void setObstaclesDirection(ObstaclesDirection Dir);
        void setObstaclesSize(float W, float H);
        void setObstaclesTexture(SDL_Texture* Texture);
        void setZIndex(uint8_t Z);

        void setSpawnRate(float Seconds);

        void Update();

    private:
        void Countdown();
        void SpawnHandler();

    // VARIABLES
    private:

        std::vector<float> OBSTACLES_SPAWNPOINTS;

        // Hay que sustituirlo por una clase para hacer las colisiones con el personaje
        std::array<Sprite, 20> OBSTACLES;
        eClock ZoneTimer;
        
        Sprite Background;
        eText COUNTDOWN;

        uint16_t ZONE_TIME_seconds;
        float ObstaclesSpeed;
        float SpawnFrom;
        float SpawnTo;
        float XY_Aux;

        
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