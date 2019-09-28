#include "Game.hpp"
#include "ASSETS_IDs.hpp"

#define FRAMERATE 60.f
#define UPDATE_STEP 30.f

Game::Game()
:dt(0), accumulator(0), tick(0)
{
    masterClock.restart();
    AssetManager* Assets = AssetManager::Instance();
	LeftArea.setZoneBackground(Assets->getTexture(WHITE_BACKGROUND), 0, 0, 240, 272);
    LeftArea.setObstaclesSize(15, 15);
    LeftArea.setObstaclesDirection(ObstaclesDirection::Top2Bottom);
    LeftArea.setObstaclesTexture(Assets->getTexture(BLACKCUBE));
    LeftArea.setObstacleInitialAndMaxVelocity(5, 50);
    LeftArea.setSpawnAreaAndDivisions(0, 242, -20, 10);
    LeftArea.setSpawnRate(0.5);
    LeftArea.setZoneTime(12);
    LeftArea.setZIndex(3);

	RightArea.setZoneBackground(Assets->getTexture(BLACK_BACKGROUND), 240, 0, 240, 272);
    RightArea.setObstaclesSize(15, 15);
    RightArea.setObstaclesDirection(ObstaclesDirection::Bottom2Top);
    RightArea.setObstaclesTexture(Assets->getTexture(WHITECUBE));
    RightArea.setObstacleInitialAndMaxVelocity(10, 20);
    RightArea.setSpawnAreaAndDivisions(240, 480, 292, 5);
    RightArea.setSpawnRate(0.5);
    RightArea.setZoneTime(12);
    RightArea.setZIndex(4);


    setMiddle(240);
}

Game::~Game(){

}

void Game::Update(){
    dt = masterClock.restart().asSeconds();

    //Spiral of death
    if(dt > 0.25f)   dt = 0.25f;

    accumulator += dt;

    // FIXED UPDATE
    while(accumulator >= 1/UPDATE_STEP){
        HERO.FixedUpdate();

        setHeroToZone();

        LeftArea.FixedUpdate();
        RightArea.FixedUpdate();
        HERO.saveCurrentState();

        accumulator -= 1/UPDATE_STEP;
    }


    // Tick para interpolar
    tick = std::min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));

    HERO.Interpolate(tick);
    LeftArea.InterpolateObstacles(tick);
    RightArea.InterpolateObstacles(tick);
}

void Game::setHeroToZone(){
    if(HERO.getPositionX() < 240 ){
        RightArea.setObstacleInitialAndMaxVelocity(SLOWVEL,SLOWVEL);
        LeftArea.setObstacleInitialAndMaxVelocity(5,50);
    }else{
        LeftArea.setObstacleInitialAndMaxVelocity(SLOWVEL,SLOWVEL);
        RightArea.setObstacleInitialAndMaxVelocity(5,50);

    }
}