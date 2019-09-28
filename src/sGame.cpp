#include "sGame.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/AssetManager.hpp"
#include "ASSETS_IDs.hpp"
#include "Score.hpp"

#define FRAMERATE 60.f
#define UPDATE_STEP 30.f

sGame::sGame()
:dt(0), accumulator(0), tick(0), SCORE(0), ActiveZone(&LeftArea)
{
    CurrentUpdate = &sGame::NormalUpdate;
}

sGame::~sGame(){

}

void sGame::queryAlert(SDL_Texture* T, float X, float Y, float W, float H, float DisplayTime, float FlickerInterval){
    CurrentUpdate = &sGame::AlertUpdate;
    ALERT.Image.setTexture(T);
    ALERT.Image.setPosition(X, Y);
    ALERT.Image.setSize(W, H);

    ALERT.setDisplayingTime(50);
    ALERT.setFlickeringInterval(FlickerInterval);
    ALERT.ResetClock();
}

void sGame::Init(){
    AssetManager* Assets = AssetManager::Instance();
    Assets->loadInitialAssets();

	LeftArea.setZoneBackground(Assets->getTexture(WHITE_BACKGROUND), 0, 0, 240, 272);
    LeftArea.setObstaclesSize(15, 15);
    LeftArea.setObstaclesDirection(ObstaclesDirection::Top2Bottom);
    LeftArea.setObstaclesTexture(Assets->getTexture(BLACKCUBE));
    LeftArea.setObstacleInitialAndMaxVelocity(3, 15);
    LeftArea.setSpawnAreaAndDivisions(0, 242, -20, 10);
    LeftArea.setSpawnRate(0.25);
    LeftArea.setZoneTime(50);
    LeftArea.setZIndex(3);

	RightArea.setZoneBackground(Assets->getTexture(BLACK_BACKGROUND), 240, 0, 240, 272);
    RightArea.setObstaclesSize(15, 15);
    RightArea.setObstaclesDirection(ObstaclesDirection::Bottom2Top);
    RightArea.setObstaclesTexture(Assets->getTexture(WHITECUBE));
    RightArea.setObstacleInitialAndMaxVelocity(10, 20);
    RightArea.setSpawnAreaAndDivisions(240, 480, 292, 5);
    RightArea.setSpawnRate(0.5);
    RightArea.setZoneTime(50);
    RightArea.setZIndex(4);

    HERO.Init(&LeftArea, &RightArea);
    setMiddle(240);
    CurrentUpdate = &sGame::NormalUpdate;
    masterClock.restart();

    LeftArea.setAlertTargetInstance(this);
    RightArea.setAlertTargetInstance(this);
}

void sGame::Update(){
    (this->*CurrentUpdate)();
}

void sGame::AlertUpdate(){
    if(ALERT.Update())
        CurrentUpdate = &sGame::NormalUpdate;

    NormalUpdate();
}

void sGame::NormalUpdate(){

    dt = masterClock.restart().asSeconds();

    SCORE += dt * 10;

    //Spiral of death
    if(dt > 0.25f)   dt = 0.25f;

    accumulator += dt;

    // FIXED UPDATE
    while(accumulator >= 1/UPDATE_STEP){

        HERO.FixedUpdate();
      
        GameHandler.ShowWarning(HERO.getPositionX(), LeftArea, RightArea );
        setHeroToZone();

        LeftArea.FixedUpdate();
        RightArea.FixedUpdate();
        
        ActiveZone->checkPlayerCollisions(HERO.getPosition(), HERO.getSize());
        HERO.saveCurrentState();

        accumulator -= 1/UPDATE_STEP;
    }

    // Tick para interpolar
    tick = std::min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));

    HERO.Interpolate(tick);
    LeftArea.InterpolateObstacles(tick);
    RightArea.InterpolateObstacles(tick);
}

void sGame::Exit(){
    JamEngine::Instance()->clearAllDrawables();
    SCORE_S::Instance()->SCORE = SCORE;
}


void sGame::setHeroToZone(){
    if(HERO.getPositionX() < 240 ){
        RightArea.setObstacleInitialAndMaxVelocity(SLOWVEL,SLOWVEL);
        LeftArea.setObstacleInitialAndMaxVelocity(3,8);
        ActiveZone = &LeftArea;
    }else{
        LeftArea.setObstacleInitialAndMaxVelocity(SLOWVEL,SLOWVEL);
        RightArea.setObstacleInitialAndMaxVelocity(3,8);
        ActiveZone = &RightArea;
    }
}