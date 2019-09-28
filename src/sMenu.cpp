#include "sMenu.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/EventManager.hpp"
#include "engineModules/StateMachine.hpp"
#include "sGame.hpp"

sMenu::sMenu()
:PRESS_STARTO(200, 150)
{
    PRESS_STARTO.setString("PRESS ANY KEY TO STARTO");
    JamEngine::Instance()->setDrawable_ZIndex(&PRESS_STARTO, 2);
}


sMenu::~sMenu(){

}


void sMenu::Init(){

}

void sMenu::Update(){
    if(EventManager::Instance()->isAnyKeyPressed()){
        StateMachine::Instance()->setState(new sGame);
    }
}

void sMenu::Exit(){
    JamEngine::Instance()->clearAllDrawables();
    AssetManager::Instance()->freeTextures();
}