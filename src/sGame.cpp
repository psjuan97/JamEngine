#include "sGame.hpp"
#include "engineModules/JamEngine.hpp"
#include "engineModules/AssetManager.hpp"
#include "ASSETS_IDs.hpp"
#include "Score.hpp"

#define FRAMERATE 60.f
#define UPDATE_STEP 30.f

#define SWITCH_LEVEL_INTERVAL 10
#define LEVEL_DELAY_START 1

sGame::sGame()
:dt(0), accumulator(0), tick(0), SCORE(0), ActiveZone(&LeftArea), LevelIterator(0), WaitForDelay(0), 
 DelayAccumulator(0), ChangeLevelAccumulator(0), TelonTarget(nullptr), TotalAreaClearTelon(false)
{

    randMap = rand()%2;
    CurrentUpdate = &sGame::NormalUpdate;


    ArrowPos[0] = {60,  220};
    ArrowPos[1] = {60,   20};
    ArrowPos[2] = {330,  20};
    ArrowPos[3] = {330, 220};
    ArrowPos[4] = {20,   110};
    ArrowPos[5] = {430,  110};

    //  LEFT: PspDirTarget {0, 1} | ObstaclesDir { Top2Bottom, Bottom2Top}
    // RIGHT: PspDirTarget {2, 3} | ObstaclesDir { Top2Bottom, Bottom2Top}
    // TOTAL: PspDirTarget {4, 5} | ObstaclesDir { ALL }

    // PRESET 0
    RUN_PRESETS[0][0] = {AreaType::TOTAL_AREA, 5, ObstaclesDirection::Left2Right, 12, 0.3};
    RUN_PRESETS[0][1] = {AreaType::LEFT_AREA, 0, ObstaclesDirection::Top2Bottom, 9, 0.5};
    RUN_PRESETS[0][2] = {AreaType::TOTAL_AREA, 4, ObstaclesDirection::Right2Left, 12, 0.4};
    RUN_PRESETS[0][3] = {AreaType::RIGHT_AREA, 2, ObstaclesDirection::Bottom2Top, 9, 0};
    RUN_PRESETS[0][4] = {AreaType::LEFT_AREA, 0, ObstaclesDirection::Top2Bottom, 10, 0};

    // PRESET 1
    RUN_PRESETS[1][0] = {AreaType::LEFT_AREA, 0, ObstaclesDirection::Top2Bottom, 8, 0.3};
    RUN_PRESETS[1][1] = {AreaType::LEFT_AREA, 1, ObstaclesDirection::Bottom2Top, 8, 0.3};
    RUN_PRESETS[1][2] = {AreaType::TOTAL_AREA, 5, ObstaclesDirection::Left2Right, 13, 0.5};
    RUN_PRESETS[1][3] = {AreaType::RIGHT_AREA, 2, ObstaclesDirection::Bottom2Top, 9, 0.5};
    RUN_PRESETS[1][4] = {AreaType::LEFT_AREA, 0, ObstaclesDirection::Top2Bottom, 10, 0.3};

    TELON[0].setTexture(AssetManager::Instance()->getTexture(TELON_TEXTURE));
    TELON[0].setSize(240, 272);
    TELON[0].setPosition(0, 0);
    TELON[1].setTexture(AssetManager::Instance()->getTexture(TELON_TEXTURE));
    TELON[1].setSize(240, 272);
    TELON[1].setPosition(240, 0);



}

sGame::~sGame(){

}

void sGame::queryAlert(SDL_Texture* T, float X, float Y, float W, float H, float DisplayTime, float FlickerInterval){
    CurrentUpdate = &sGame::AlertUpdate;
    ALERT.Image.setTexture(T);
    ALERT.Image.setPosition(X, Y);
    ALERT.Image.setSize(W, H);

    ALERT.setDisplayingTime(DisplayTime);
    ALERT.setFlickeringInterval(FlickerInterval);
    ALERT.ResetClock();
}

void sGame::Init(){
    AssetManager* Assets = AssetManager::Instance();
        std::cout << "starting loading all assetsd" << std::endl;

    //Assets->loadInitialAssets();

    cover.setTexture(Assets->getTexture(COVER));
    cover.setX(0);
    cover.setY(0);
    cover.setSize(480,272);

    JamEngine::Instance()->setDrawable_ZIndex(&cover,9);

	LeftArea.setZoneBackground(Assets->getTexture(WHITE_BACKGROUND), 0, 0, 240, 272);
    LeftArea.setObstaclesSize(15, 15);
    //LeftArea.setObstaclesTexture(Assets->getTexture(GREENCUBE));
    LeftArea.setObstaclesAnim(GREENENEMYANIM);
    LeftArea.setSpawnRate(0.25);
    LeftArea.setZIndex(3);

	RightArea.setZoneBackground(Assets->getTexture(BLACK_BACKGROUND), 240, 0, 240, 272);
    RightArea.setObstaclesSize(15, 15);
    //RightArea.setObstaclesTexture(Assets->getTexture(PINKCUBE));
    RightArea.setObstaclesAnim(PINKENEMYANIM);
    RightArea.setSpawnRate(0.5);
    RightArea.setZIndex(4);

	TotalArea.setZoneBackground(Assets->getTexture(BLACK_BACKGROUND), 0, 0, 480, 272);
    TotalArea.setObstaclesSize(15, 15);
    TotalArea.setObstaclesAnim(PINKENEMYANIM);
    TotalArea.setSpawnRate(0.5);
    TotalArea.setZIndex(5);



    HERO.Init(&LeftArea, &RightArea);
    setMiddle(240);
    CurrentUpdate = &sGame::NormalUpdate;
    masterClock.restart();

    setTransition();

    JamEngine::Instance()->setDrawable_ZIndex(&TELON[0], 8);
    JamEngine::Instance()->setDrawable_ZIndex(&TELON[1], 8);
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

    ChangeLevelAccumulator+=dt;

    SCORE += dt * 10;

    if(ChangeLevelAccumulator > SWITCH_LEVEL_INTERVAL)
        setTransition();

    //Spiral of deathChangeLevelAccumulator
    if(dt > 0.25f)   dt = 0.25f;
    
    accumulator += dt;

    // FIXED UPDATE
    while(accumulator >= 1/UPDATE_STEP){


        GameHandler.ShowWarning(HERO.getPositionX(), LeftArea, RightArea );
        setHeroToZone();

        checkForDelay();
        
        HERO.FixedUpdate();


        HERO.saveCurrentState();
        accumulator -= 1/UPDATE_STEP;
    }

    // Tick para interpolar
    tick = std::min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));

    HERO.Interpolate(tick);

    ActiveZone->InterpolateObstacles(tick);

    JamEngine::Instance()->Update();
}

void sGame::Exit(){
    JamEngine::Instance()->clearAllDrawables();
    SCORE_S::Instance()->SCORE = SCORE;
}


void sGame::setHeroToZone(){
    // if(HERO.getPositionX() < 240 ){
    //     RightArea.setObstacleInitialAndMaxVelocity(SLOWVEL,SLOWVEL);
    //     LeftArea.setObstacleInitialAndMaxVelocity(3,8);
    //     ActiveZone = &LeftArea;
    // }else{
    //     LeftArea.setObstacleInitialAndMaxVelocity(SLOWVEL,SLOWVEL);
    //     RightArea.setObstacleInitialAndMaxVelocity(3,8);
    //     ActiveZone = &RightArea;
    // }
}

void sGame::setTransition(){

    LEVEL& Next = RUN_PRESETS[randMap][LevelIterator];
    
    if(Next.Type == AreaType::LEFT_AREA){
        LeftArea.setObstaclesDirection(Next.ObstaclesDir);
        LeftArea.setObstacleInitialAndMaxVelocity(Next.InitialObstacleSpeed, 0);
        
        if(Next.ObstaclesDir == ObstaclesDirection::Top2Bottom)
            LeftArea.setSpawnAreaAndDivisions(0, 242, -20, 10);
        else
            LeftArea.setSpawnAreaAndDivisions(0, 242, 292, 10);

        
        uint8_t ID = ARROW_UP;
        if(Next.PspDirTarget == 0)
            ID = ARROW_DOWN;
    
        queryAlert(AssetManager::Instance()->getTexture(ID), ArrowPos[Next.PspDirTarget].ArrowPositionX, ArrowPos[Next.PspDirTarget].ArrowPositionY, 59, 34, 0.7, 0.09);

        if(ActiveZone != &LeftArea)
            HERO.SetPosition(120, 136);
        
        ActiveZone = &LeftArea;

        TELON[1].Visibility = true;
        TelonTarget = &TELON[0];
        
        TotalAreaClearTelon = false;
        TotalArea.enableDisableBackground(false);
        RightArea.CleanZone();
        TotalArea.CleanZone();

        HERO.setBounds(0);
    }
    else if(Next.Type == AreaType::RIGHT_AREA){
        RightArea.setObstaclesDirection(Next.ObstaclesDir);
        RightArea.setObstacleInitialAndMaxVelocity(Next.InitialObstacleSpeed, 0);

        if(Next.ObstaclesDir == ObstaclesDirection::Top2Bottom)
            RightArea.setSpawnAreaAndDivisions(242, 480, -20, 10);
        else
            RightArea.setSpawnAreaAndDivisions(240, 480, 292, 10);


        uint8_t ID = ARROW_UP;
        if(Next.PspDirTarget == 3)
            ID = ARROW_DOWN;
        queryAlert(AssetManager::Instance()->getTexture(ID), ArrowPos[Next.PspDirTarget].ArrowPositionX, ArrowPos[Next.PspDirTarget].ArrowPositionY, 59, 34, 0.7, 0.09);
        
        if(ActiveZone != &RightArea)
            HERO.SetPosition(360, 136);

        ActiveZone = &RightArea;
        TELON[0].Visibility = true;

        TelonTarget = &TELON[1];


        TotalAreaClearTelon = false;
        TotalArea.enableDisableBackground(false);
        LeftArea.CleanZone();
        TotalArea.CleanZone();
        HERO.setBounds(1);
    }
    else{
        TotalArea.setObstaclesDirection(Next.ObstaclesDir);
        TotalArea.setObstacleInitialAndMaxVelocity(Next.InitialObstacleSpeed, 0);
        TotalArea.setSpawnRate(0.2);

        if(Next.ObstaclesDir == ObstaclesDirection::Top2Bottom){
            TotalArea.setSpawnAreaAndDivisions(0, 480, -20, 10);
            TotalArea.setObstaclesSize(40, 15);
        }
        else if(Next.ObstaclesDir == ObstaclesDirection::Bottom2Top){
            TotalArea.setSpawnAreaAndDivisions(0, 480, 292, 10);
            TotalArea.setObstaclesSize(40, 15);
            
        }
        else if(Next.ObstaclesDir == ObstaclesDirection::Left2Right){
            TotalArea.setSpawnAreaAndDivisions(0, 272, -20, 10);
            TotalArea.setObstaclesSize(15, 40);

        }
        else{
            TotalArea.setSpawnAreaAndDivisions(0, 272, 500, 10);
            TotalArea.setObstaclesSize(15, 40);

        }

        uint8_t ID = ARROW_RIGHT;
        if(Next.PspDirTarget == 4)
            ID = ARROW_LEFT;

        queryAlert(AssetManager::Instance()->getTexture(ID), ArrowPos[Next.PspDirTarget].ArrowPositionX, ArrowPos[Next.PspDirTarget].ArrowPositionY, 34, 59, 0.7, 0.09);

        if(ActiveZone != &TotalArea)
            HERO.SetPosition(240, 136);

        ActiveZone = &TotalArea;
        TELON[0].Visibility = true;
        TELON[1].Visibility = true;
        TelonTarget = &TELON[1];

        
        TotalAreaClearTelon = true;

        TotalArea.enableDisableBackground(true);
        LeftArea.CleanZone();
        RightArea.CleanZone();
        HERO.setBounds(2);
    }

    ++LevelIterator;
    if(LevelIterator >= 5)
        LevelIterator = 0;

    DelayAccumulator = 0;
    ChangeLevelAccumulator = 0;
    WaitForDelay = true;
}


#include <iostream>
void sGame::checkForDelay(){
    if(WaitForDelay){
        DelayAccumulator += 1/UPDATE_STEP;
        if(DelayAccumulator > LEVEL_DELAY_START){
            WaitForDelay = false;
            ActiveZone->resetClock();
            if(TotalAreaClearTelon){
                TELON[0].Visibility = false;
                TELON[1].Visibility = false;
            }
            else
                TelonTarget->Visibility = false;
            ChangeLevelAccumulator = 0;
        }
    }
    else{

        ActiveZone->checkPlayerCollisions(HERO.getPosition(), HERO.getSize());
        ActiveZone->FixedUpdate();
    }
}