#ifndef GAME_H
#define GAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"
#include "Zone.hpp"
#include "Handler.hpp"

class Game{
    // METHODS
    public:
        Game();
        Game(const Game& orig) = delete;
        ~Game();

        void Update();

    // VARIABLES
    private:
        //Entities
	    Player HERO;
        
        Zone LeftArea;
        Zone RightArea;
        
        Handler GameHandler;

        // Interpolation things
        eClock masterClock;

        double dt;
        float accumulator;
        double tick;
};

#endif