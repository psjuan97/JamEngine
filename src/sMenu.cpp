#include "sMenu.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/EventManager.hpp"
#include "engineModules/StateMachine.hpp"
#include "sGame.hpp"
#include "ASSETS_IDs.hpp"

sMenu::sMenu()
{

}


sMenu::~sMenu(){

}


void sMenu::Init(){
    
    AssetManager::Instance()->loadInitialAssets();

    SplashSprite.setTexture(AssetManager::Instance()->getTexture(SPLASH));
    SplashSprite.setSize(480, 280);
    SplashSprite.setPosition(0, 0);
    SplashSprite.Visibility = false;
   
    JamEngine::Instance()->setDrawable_ZIndex(&SplashSprite, 3, 0);

    bool i = false;
    for (int i = 0; i <= 200; ++i) {
        JamEngine::Instance()->DrawUno(3, 0);
    }

    MenuStartSprite.setTexture(AssetManager::Instance()->getTexture(MENUSTART));
    MenuStartSprite.setSize(480, 280);
    MenuStartSprite.setPosition(0, 0);
    MenuStartSprite.Visibility = true;


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