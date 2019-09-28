#ifndef HANDLER_H
#define HANDLER_H

#include "engineModules/EventManager.hpp"
#include "Interpolable_Object.hpp"

class Handler {
    public:
        Handler();
        ~Handler();

        void handleEvents();
        void ShowWarning();

    private:
        Sprite WarningSprite;
        EventManager* eventManager;
};

#endif