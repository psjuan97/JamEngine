#include <stdio.h>
#include <iostream>

#include "EventManager.hpp"

EventManager::EventManager(){

    for(int i = 0;  i < MAXEvents ; i++){
        callbacks[i] = nullptr;
    }

}

EventManager::~EventManager(){

}

void EventManager::launch(){
    SDL_Event event;

    while (SDL_PollEvent(&event)) { //algun evento?
        //std::cout << "Evento registrado " << std::endl;
        //std::cout << "boton" << (int) event.jbutton.button << " " << std::endl; 
        if(callbacks[(int) event.jbutton.button ] != nullptr){
           //std::cout << "Ejecutando evento..." << std::endl;
            ((void (*)(void)) callbacks[(int) event.jbutton.button ])();

        }

    }

}

void EventManager::registerEvent(PspCtrlButtons key, void* callback){
    callbacks[static_cast<int>(key)] = callback;
}