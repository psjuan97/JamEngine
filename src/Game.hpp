#ifndef GAME_H
#define GAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"
#include "Zone.hpp"

class Game{
    // METHODS
    public:
        static Game* Instance(){
            static Game instance;
            return &instance;
        }
        ~Game();

        void Update();
        void queryAlert(SDL_Texture* T, float X, float Y, float W, float H, float DisplayTime, float FlickerInterval);

    private:
        Game();
        Game(const Game& orig) = delete;
        void operator=(const Game& orig) = delete;

        void NormalUpdate();
        void AlertUpdate();

    // VARIABLES
    public:
        //PopUp ALERT;
    private:

        //Entities
	    Player HERO;
        
        Zone LeftArea;
        Zone RightArea;
        
        PopUp ALERT;

        // Interpolation things
        eClock masterClock;

        double dt;
        float accumulator;
        double tick;

        void (Game::*CurrentUpdate)();
};

#endif