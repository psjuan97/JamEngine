#ifndef HANDLER_H
#define HANDLER_H

#include "engineModules/EventManager.hpp"
#include "Interpolable_Object.hpp"
#include "Zone.hpp"

class Handler {
    public:
        Handler();
        ~Handler();

        void ShowWarning(float hero_x, Zone& LeftArea, Zone& RightArea);

    private:
        Sprite WarningSprite;
        EventManager* eventManager;
};

#endif