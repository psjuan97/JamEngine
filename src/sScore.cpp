#include "sScore.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/AssetManager.hpp"
#include "engineModules/EventManager.hpp"
#include "Score.hpp"
#include "sMenu.hpp"

sScore::sScore()
:FINAL_SCORE(100, 50), AGAIN(200, 50)
{}

sScore::~sScore(){

}

void sScore::Init(){
    FINAL_SCORE.setString(to_string(SCORE_S::Instance()->SCORE));
    AGAIN.setString("AGAIN?");

    JamEngine::Instance()->setDrawable_ZIndex(&FINAL_SCORE, 3);
    JamEngine::Instance()->setDrawable_ZIndex(&AGAIN, 3);
}

void sScore::Update(){
    if(EventManager::Instance()->isAnyKeyPressed()){
        StateMachine::Instance()->setState(new sMenu);
    }
}

void sScore::Exit(){
    JamEngine::Instance()->clearAllDrawables();
}