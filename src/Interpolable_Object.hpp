#ifndef INTERPOLABLE_OBJECT
#define INTERPOLABLE_OBJECT

#include "math/Vector2.hpp"

class Interpolable_Object{
    public:
        void savePreviousState();
        void saveCurrentState();
        virtual void Interpolate(float Tick) = 0;

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