#ifndef GAME_H
#define GAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"
#include "Zone.hpp"
#include "Handler.hpp"
#define SLOWVEL 2

class Game{
    // METHODS
    public:
        Game();
        Game(const Game& orig) = delete;
        ~Game();

        void Update();
        void setHeroToZone();

        inline void setMiddle(uint16_t middle){
            middleX = middle;
        };
    // VARIABLES
    private:
        //Entities
	    Player HERO;
        
        Zone LeftArea;
        Zone RightArea;
        
        Handler GameHandler;
        uint16_t middleX;

        // Interpolation things
        eClock masterClock;

        double dt;
        float accumulator;
        double tick;
};

#endif