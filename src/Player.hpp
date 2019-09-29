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
        void SetPosition(float X, float Y);
        inline void setBounds(uint8_t id){
            BoundsID = id;
        };

        virtual void Interpolate(float tick);


        inline math::Vector2f getSize(){
            return PlayerSprite.getSize(); 
        }

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

        struct Bounds{
            float minX, maxX;
        };

        Bounds ZONE_X_BOUNDS[3];

       // Sprite PlayerSprite;
        AnimatedSprite PlayerSprite;
        
        EventManager* eventManager;

        Zone* leftArea;
        Zone* rightArea;

        uint8_t BoundsID;
};

#endif