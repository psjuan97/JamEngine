#ifndef PLAYER_H
#define PLAYER_H

#include "engineModules/AnimatedSprite.hpp"
#include <array>

#include "engineModules/EventManager.hpp"
#include "Interpolable_Object.hpp"


class Player : public Interpolable_Object {
    // METHODS
    public:
        Player();
        Player(const Player& orig) = delete;
        ~Player();

        void Init();

        void FixedUpdate();

        virtual void Interpolate(float tick);

    private:

        void Dash();
        void Skill2();

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
};

#endif