#include "sScore.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/AssetManager.hpp"
#include "engineModules/EventManager.hpp"
#include "Score.hpp"
#include "sMenu.hpp"
#include "sGame.hpp"

#include "ASSETS_IDs.hpp"

/// :FINAL_SCORE(200, 50), AGAIN(100, 50)
sScore::sScore()
:FINAL_SCORE(290, 170), AGAIN(140, 170), ANYKEY(130, 200)
{}

sScore::~sScore(){

}

void sScore::Init(){
    EndGameSprite.setTexture(AssetManager::Instance()->getTexture(MENUFIN));
    EndGameSprite.setSize(480, 280);
    EndGameSprite.setPosition(0, 0);
    EndGameSprite.Visibility = true;
    JamEngine::Instance()->setDrawable_ZIndex(&EndGameSprite, 2);

    FINAL_SCORE.setString(to_string(SCORE_S::Instance()->SCORE));
    AGAIN.setString("FINAL SCORE: ");
    ANYKEY.setString("press any key to play again");
    
    JamEngine::Instance()->setDrawable_ZIndex(&FINAL_SCORE, 4);
    JamEngine::Instance()->setDrawable_ZIndex(&AGAIN, 3);
    JamEngine::Instance()->setDrawable_ZIndex(&ANYKEY, 3);
    
}

void sScore::Update(){
    if(EventManager::Instance()->isAnyKeyPressed()){
        StateMachine::Instance()->setState(new sGame);
    }
}

void sScore::Exit(){
    JamEngine::Instance()->clearAllDrawables();
}