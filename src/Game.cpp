#include "Game.hpp"

#define FRAMERATE 60.f
#define UPDATE_STEP 30.f

Game::Game()
:dt(0), accumulator(0), tick(0)
{
    masterClock.restart();
}

Game::~Game(){

}

void Game::Update(){
    dt = masterClock.restart().asSeconds();

    //Spiral of death
    if(dt > 0.25f)   dt = 0.25f;

    accumulator += dt;
    while(accumulator >= 1/UPDATE_STEP){
        HERO.FixedUpdate();


        HERO.SaveCurrentState();

        accumulator -= 1/UPDATE_STEP;
    }

    // Tick para interpolar
    tick = std::min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));


    HERO.Interpolate(tick);
}