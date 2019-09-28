#ifndef SGAME_H
#define SGAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"
#include "Zone.hpp"
#include "engineModules/State.hpp"

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

        void queryAlert(SDL_Texture* T, float X, float Y, float W, float H, float DisplayTime, float FlickerInterval);

    private:

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

        void (sGame::*CurrentUpdate)();
};

#endif