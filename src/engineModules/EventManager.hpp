#pragma once

#include <SDL2/SDL.h>

#define MAXEvents 255

enum PspCtrlButtons  {
    TRIANGLE = 0,  CIRCLE,  CROSS,  SQUARE,
    LTRIGGER,  RTRIGGER,
    DOWN,  LEFT,  UP,  RIGHT,
    SELECT,  START,  HOME,  HOLD, JOY,
    PSPKEYCOUNT
};



class EventManager{
    public:
        static EventManager* Instance(){
            static EventManager instance;
            return &instance;
        }

        ~EventManager();

        void launch(); // execute all callbacks from the list

        // Devuelve el estado de un botón
        inline bool getButtonState(PspCtrlButtons BUTTON){
            return PSP_BUTTONS_STATE[BUTTON];
        }

        // Devuelve y pone a false el estado de un botón
        inline bool getAndResetButtonState(PspCtrlButtons BUTTON){
            bool RESULT = PSP_BUTTONS_STATE[BUTTON];
            PSP_BUTTONS_STATE[BUTTON] = false;
            return RESULT;
        }

        bool isAnyKeyPressed();

    private:
        EventManager();
        EventManager(const EventManager& orig) = delete;
        void operator=(const EventManager &orig) = delete;


    private:
        // using pMethod = void(Player::*)();
        
        // pMethod callbacks[MAXEvents] = {0};


        
        bool PSP_BUTTONS_STATE[PspCtrlButtons::PSPKEYCOUNT];

};