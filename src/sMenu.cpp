#include "sMenu.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/EventManager.hpp"
#include "engineModules/StateMachine.hpp"
#include "sGame.hpp"
#include "ASSETS_IDs.hpp"

sMenu::sMenu()
{
   // PRESS_STARTO.setString("PRESS ANY KEY TO STARTO");
}


sMenu::~sMenu(){

}


void sMenu::Init(){
    
    AssetManager::Instance()->loadInitialAssets();

    MenuStartSprite.setTexture(AssetManager::Instance()->getTexture(MENUSTART));
    MenuStartSprite.setSize(480, 280);
    MenuStartSprite.setPosition(0, 0);
    MenuStartSprite.Visibility = true;
   // JamEngine::Instance()->setDrawable_ZIndex(&PRESS_STARTO, 2);
    JamEngine::Instance()->setDrawable_ZIndex(&MenuStartSprite, 2);
    
}

void sMenu::Update(){
    if(EventManager::Instance()->isAnyKeyPressed()){
        StateMachine::Instance()->setState(new sGame);
    }
}

void sMenu::Exit(){
    JamEngine::Instance()->clearAllDrawables();
}