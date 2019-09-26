#pragma once

#include <SDL2/SDL.h>

#define MAXEvents 255



enum class  PspCtrlButtons  {
    TRIANGLE = 0,  CIRCLE,  CROSS,  SQUARE,
    LTRIGGER,  RTRIGGER,
    DOWN,  LEFT,  UP,  RIGHT,
    SELECT,  START,  HOME,  HOLD 
    };



class EventManager{
public:
    static EventManager* Instance(){
        static EventManager instance;
        return &instance;
    }

    ~EventManager();

    
    void registerEvent(PspCtrlButtons key, void* callback);
    void launch(); // execute all callbacks from the list


    private:
        EventManager();
        EventManager(const EventManager& orig) = delete;
        void operator=(const EventManager &orig) = delete;
private:
    void* callbacks[MAXEvents] = {0};

};