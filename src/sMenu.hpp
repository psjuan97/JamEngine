#ifndef SMENU_H
#define SMENU_H

#include "engineModules/State.hpp"
#include "engineModules/eText.hpp"
#include "engineModules/Sprite.hpp"

class sMenu : public State {
    public: 
        sMenu();
        sMenu(const sMenu& orig);
        ~sMenu();

        virtual void Init();
        virtual void Update();
        virtual void Exit();

    private:
        //eText PRESS_STARTO;
        Sprite MenuStartSprite;
        Sprite SplashSprite;
};

#endif