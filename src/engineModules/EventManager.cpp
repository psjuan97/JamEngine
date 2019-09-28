#include <stdio.h>
#include <iostream>

#include "EventManager.hpp"

#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540


#define JOYSTICK_DEAD_ZONE  8000


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

        if(event.type == SDL_JOYAXISMOTION){
            std::cout << event.jaxis.value << std::endl;
            

                         //X axis motion
							if( event.jaxis.axis == 0 )
							{
                                 //Left of dead zone
                                if( event.jaxis.value < -JOYSTICK_DEAD_ZONE )
                                {
                                    PSP_BUTTONS_STATE[LEFT] = true;
                                }
                                //Right of dead zone
                                else if( event.jaxis.value > JOYSTICK_DEAD_ZONE )
                                {
                                    PSP_BUTTONS_STATE[RIGHT] = true;
                                }
                                else
                                {
     
                                    PSP_BUTTONS_STATE[LEFT] = false;
                                    PSP_BUTTONS_STATE[RIGHT] = false;
                                }
							}
							//Y axis motion
							else if( event.jaxis.axis == 1 )
							{
								//Below of dead zone
								if( event.jaxis.value < -JOYSTICK_DEAD_ZONE )
								{
                                     PSP_BUTTONS_STATE[UP] = true;
								}
								//Above of dead zone
								else if( event.jaxis.value > JOYSTICK_DEAD_ZONE )
								{
                                    PSP_BUTTONS_STATE[DOWN] = true;								
								}
								else
								{
                                    PSP_BUTTONS_STATE[DOWN] = false;
                                    PSP_BUTTONS_STATE[UP] = false;								
							}


                            }

        }

    }

}

bool EventManager::isAnyKeyPressed(){
    for(uint8_t i = 0; i < PspCtrlButtons::PSPKEYCOUNT; ++i){
        if(PSP_BUTTONS_STATE[i])
            return true;
    }

    return false;
}


void EventManager::registerEvent(PspCtrlButtons key, void* callback){
    //callbacks[static_cast<int>(key)] = callback;
}