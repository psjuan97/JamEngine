#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Interpolable_Object.hpp"
#include "engineModules/Sprite.hpp"
#include "engineModules/Animation.hpp"
#include "engineModules/AnimatedSprite.hpp"

#include "enumObstacleDir.hpp"


class Obstacle : public Interpolable_Object {
    friend class Zone;
    // METHODS
    public:
        Obstacle();
        Obstacle(const Obstacle& orig);
        ~Obstacle();

        void setObstacleSpeed(math::Vector2f _SPEED, float MAX);

        void FixedUpdate(float BoostTick);
        virtual void Interpolate(float tick);

        inline bool isAlive(){
            return alive;
        }

        void setSlow(bool slow);
    private:
        void checkBounds();

    // VARIABLES
    private:
        AnimatedSprite ObstacleSprite;
        float BaseSpeed;
        float SpeedBoostPercentage;
        ObstaclesDirection Direction;
        bool alive;

};

#endif