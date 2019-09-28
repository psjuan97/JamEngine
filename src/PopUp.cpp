#include "PopUp.hpp"

PopUp::PopUp()
:DisplayingTime(0), FlickeringInterval(0), DisplayAccumulator(0), FlickerAccumulator(0)
{
    Image.Visibility = false;
}

PopUp::~PopUp(){}

void PopUp::setDisplayingTime(float Seconds){
    JamEngine::Instance()->setDrawable_ZIndex(&Image, 9);

    DisplayingTime = Seconds;
    ResetAccumulators();
}

void PopUp::setFlickeringInterval(float Seconds){
    FlickeringInterval = Seconds;
    ResetAccumulators();

    if(Seconds == 0){
        Image.Visibility = true;
    }
}

bool PopUp::Update(){
    float dt = clock.restart().asSeconds();
    DisplayAccumulator += dt;
    FlickerAccumulator += dt;
    
    if(FlickeringInterval > 0 && FlickerAccumulator > FlickeringInterval){
        Image.Visibility = !Image.Visibility;
        FlickerAccumulator -= FlickeringInterval;
    }

    if(DisplayAccumulator > DisplayingTime){
        Image.Visibility = false;
        ResetClock();
        return true;
    }


    return false;
}

void PopUp::ResetClock(){
    clock.restart();
}

void PopUp::ResetAccumulators(){
    DisplayAccumulator = 0;
    FlickerAccumulator = 0;
}