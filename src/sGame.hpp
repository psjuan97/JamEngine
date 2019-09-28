#ifndef SGAME_H
#define SGAME_H

#include "Player.hpp"
#include "engineModules/eClock.hpp"
#include "Zone.hpp"
#include "engineModules/State.hpp"
#include "Handler.hpp"
#define SLOWVEL 2

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

        inline void setMiddle(uint16_t middle){
            middleX = middle;
        };
    // VARIABLES
    public:
        //PopUp ALERT;
    private:

        //Entities
	    Player HERO;
        
        Zone LeftArea;
        Zone RightArea;
        
        Handler GameHandler;
        uint16_t middleX;
        PopUp ALERT;

        // Interpolation things
        eClock masterClock;

        double dt;
        float accumulator;
        double tick;

        void (sGame::*CurrentUpdate)();
};

#endif