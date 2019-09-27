#include <stdio.h>
#include <iostream>

#include "EventManager.hpp"

#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540

EventManager::EventManager(){

    // for(int i = 0;  i < MAXEvents ; i++){
    //     callbacks[i] = nullptr;
    // }

    for(uint8_t i = 0; i < PspCtrlButtons::PSPKEYCOUNT; ++i)
        PSP_BUTTONS_STATE[i] = false;

}

EventManager::~EventManager(){

}

void EventManager::launch(){
    SDL_Event event;

    while (SDL_PollEvent(&event)) { //algun evento?
        //std::cout << "Evento registrado " << std::endl;
        //std::cout << "boton" << (int) event.jbutton.button << " " << std::endl; 
        if(static_cast<int>(event.jbutton.button) < PspCtrlButtons::PSPKEYCOUNT ){
           //std::cout << "Ejecutando evento..." << std::endl;
            //((void (*)(uint32_t)) callbacks[(int) event.jbutton.button ])( event.jbutton.type);
            if(event.jbutton.type == BUTTON_DOWN)
                PSP_BUTTONS_STATE[event.jbutton.button] = true;
            else{
                PSP_BUTTONS_STATE[event.jbutton.button] = false;
            }
        }

    }

}

void EventManager::registerEvent(PspCtrlButtons key, void* callback){
    //callbacks[static_cast<int>(key)] = callback;
}