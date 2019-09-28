#ifndef PLAYER_H
#define PLAYER_H

#include "engineModules/AnimatedSprite.hpp"
#include <array>

#include "engineModules/EventManager.hpp"
#include "Interpolable_Object.hpp"
#include "Zone.hpp"

class Player : public Interpolable_Object {
    // METHODS
    public:
        Player();
        Player(const Player& orig) = delete;
        ~Player();

        void Init(Zone*, Zone*);

        void FixedUpdate();

        virtual void Interpolate(float tick);

    private:

        void Dash();
        void CleanArea();

        void CheckMovement();


    // VARIABLES
    private:

        struct Button2Func{
            PspCtrlButtons Button;
            void (Player::*Target)();
        };

        std::array<Button2Func, 2> BUTTON_MAPPING;

        Sprite PlayerSprite;

        EventManager* eventManager;

        Zone* leftArea;
        Zone* rightArea;
};

#endif