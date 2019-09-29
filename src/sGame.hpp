#ifndef SGAME_H
#define SGAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"
#include "Zone.hpp"
#include "engineModules/State.hpp"
#include "Handler.hpp"
#define SLOWVEL 2


struct ArrowPositions{
    float ArrowPositionX;
    float ArrowPositionY;
};

enum AreaType{
    LEFT_AREA = 0,
    RIGHT_AREA,
    TOTAL_AREA
};

struct LEVEL {
    AreaType Type;
    uint8_t PspDirTarget;
    ObstaclesDirection ObstaclesDir;
    float InitialObstacleSpeed;
    float Acceleration;
};


class sGame : public State {
    // METHODS
    public:
        sGame();
        sGame(const sGame& orig) = delete;
        void operator=(const sGame& orig) = delete;
        ~sGame();

        virtual void Init();
        virtual void Update();
        virtual void Exit();

        void setHeroToZone();
        void queryAlert(SDL_Texture* T, float X, float Y, float W, float H, float DisplayTime, float FlickerInterval);

    private:

        void NormalUpdate();
        void AlertUpdate();

        void setTransition();
        void checkForDelay();

        inline void setMiddle(uint16_t middle){
            middleX = middle;
        };

    // VARIABLES
    public:
        //PopUp ALERT;
    private:
        /////////////
        /// decoracion ///
        //////////////////
        Sprite cover;
        
        Sprite TELON[2];

        //Entities
	    Player HERO;

        ArrowPositions ArrowPos[6];
        std::array<LEVEL, 5> RUN_PRESETS[2];
        
        Zone LeftArea;
        Zone RightArea;
        Zone TotalArea;
        
        Handler GameHandler;
        PopUp ALERT;
        uint16_t ZONE_LAST_TIME = 0;

        // Interpolation things
        eClock masterClock;

        double dt;
        double tick;
        float accumulator;

        float SCORE;

        uint16_t middleX;

        Zone* ActiveZone;
        void (sGame::*CurrentUpdate)();

        uint8_t LevelIterator;
        bool WaitForDelay;
        float DelayAccumulator;
        float ChangeLevelAccumulator;
        Sprite* TelonTarget;
        bool TotalAreaClearTelon;


        int randMap = 0;
};

#endif