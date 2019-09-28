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

        void SavePreviousState();
        void SaveCurrentState();
        void Interpolate(float tick);

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
        math::Vector2f SPEED;
        math::Vector2f Position;

        struct State{
            math::Vector2f Position;
        };
        State Previous;
        State Current;

        EventManager* eventManager;
};

#endif