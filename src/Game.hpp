#ifndef GAME_H
#define GAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"

class Game{
    // METHODS
    public:
        Game();
        Game(const Game& orig) = delete;
        ~Game();

        void Update();

    // VARIABLES
    private:
	    Player HERO;

        eClock masterClock;

        float dt;
        float accumulator;
        double tick;
};

#endif