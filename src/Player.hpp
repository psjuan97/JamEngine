#ifndef PLAYER_H
#define PLAYER_H

#include "engineModules/AnimatedSprite.hpp"
#include <array>

#include "engineModules/EventManager.hpp"


class Player{
    // METHODS
    public:
        Player();
        Player(const Player& orig) = delete;
        ~Player();

        void FixedUpdate();


    private:
        

    // VARIABLES
    public:

    private:

        struct Button2Func{
            PspCtrlButtons Button;
            void (Player::*Target)();
        };

        void Dash();
        void Skill2();

        std::array<Button2Func, 2> BUTTON_MAPPING;

        void CheckMovement();

        AnimatedSprite aSprite;
        math::Vector2f SPEED;

        EventManager* eventManager;
};

#endif