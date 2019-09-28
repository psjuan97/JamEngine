#ifndef POPUP_H
#define POPUP_H

#include "engineModules/Sprite.hpp"
#include "engineModules/eClock.hpp"

class PopUp{

    //METHODS
    public:
        PopUp();
        PopUp(const PopUp& orig) = delete;
        ~PopUp();

        void setDisplayingTime(float Seconds);
        void setFlickeringInterval(float Seconds);

        bool Update();
        void ResetClock();
        void ResetAccumulators();
    
    // VARIABLES
    public:
        Sprite Image;

    private:
        eClock clock;
        float DisplayingTime;
        float FlickeringInterval;

        float DisplayAccumulator;
        float FlickerAccumulator;
};

#endif