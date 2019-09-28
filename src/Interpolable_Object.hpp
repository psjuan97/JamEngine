#ifndef INTERPOLABLE_OBJECT
#define INTERPOLABLE_OBJECT

#include "math/Vector2.hpp"

class Interpolable_Object{
    public:
        void savePreviousState();
        void saveCurrentState();
        virtual void Interpolate(float Tick) = 0;
        inline float getPositionX(){
            return Position.x;
        }

        inline math::Vector2f getPosition(){
            return Position;
        };

    protected:
        struct State{
            math::Vector2f Position;
        };

        State Previous;
        State Current;

        math::Vector2f SPEED;
        math::Vector2f Position;
};

#endif