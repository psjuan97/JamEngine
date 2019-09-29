#include "Player.hpp"

#include "engineModules/JamEngine.hpp"
#include "ASSETS_IDs.hpp"


#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540

#define PLAYER_SPEED 8
#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 8

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

Player::Player(){

    
    // EventManager::Instance()->registerEvent(PspCtrlButtons::LEFT, (void *)&Player::MoveLeft );
	// EventManager::Instance()->registerEvent(PspCtrlButtons::UP, (void *)&Player::MoveUp);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::RIGHT, (void *)&Player::MoveRight);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::DOWN, (void *)&Player::MoveDown);

    // Cada tecla tiene asociado un método
    BUTTON_MAPPING[0] = {PspCtrlButtons::CROSS, &Player::Dash};
    BUTTON_MAPPING[1] = {PspCtrlButtons::CIRCLE, &Player::CleanArea};

    eventManager = EventManager::Instance();
}

Player::~Player(){
    leftArea = nullptr;
    rightArea = nullptr;
}

void Player::Init(Zone* lzone, Zone* rzone){
    leftArea = lzone;
    rightArea = rzone;
    
    JamEngine::Instance()->setDrawable_ZIndex(&PlayerSprite, 9);

    PlayerSprite.setTexture(AssetManager::Instance()->getTexture(PLAYER));
    PlayerSprite.setSize(8, 8);
    PlayerSprite.setPosition(120, 136);

    Position = PlayerSprite.getPosition();
    Previous.Position = Current.Position = Position;
    PlayerSprite.setAnimation(PlayerAnim);


}

void Player::FixedUpdate(){


    savePreviousState();

    CheckMovement();

    // Comprueba si se ha pulsado un botón registrado en el mapping y ejecuta su función asociada
    for(uint8_t i = 0; i < BUTTON_MAPPING.size(); ++i){
        if(eventManager->getAndResetButtonState(BUTTON_MAPPING[i].Button))
            (this->*BUTTON_MAPPING[i].Target)();
    }

    Position += SPEED;
  
    if(Position.x < 0) Position.x = 0;
    else if (Position.x + PLAYER_WIDTH > SCREEN_WIDTH) Position.x = SCREEN_WIDTH - PLAYER_WIDTH;

    if(Position.y < 0) Position.y = 0;
    else if(Position.y + PLAYER_HEIGHT > SCREEN_HEIGHT) Position.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
}


void Player::CheckMovement(){
    int8_t X_AXIS = eventManager->getButtonState(PspCtrlButtons::RIGHT) - eventManager->getButtonState(PspCtrlButtons::LEFT);
    int8_t Y_AXIS = eventManager->getButtonState(PspCtrlButtons::DOWN) - eventManager->getButtonState(PspCtrlButtons::UP);

    SPEED.x = PLAYER_SPEED * X_AXIS;
    SPEED.y = PLAYER_SPEED * Y_AXIS;
}

#define DASH_FACTOR 4
void Player::Dash(){
    math::Vector2f AuxSpeed(SPEED.x * DASH_FACTOR, SPEED.y * DASH_FACTOR);
    Position = Position + AuxSpeed;

    JamEngine::Instance()->setBuzz(true);


}

void Player::CleanArea(){
    if (PlayerSprite.getPosition().x < 240) {
        leftArea->CleanZone();
    } else {
        rightArea->CleanZone();
    }
}




void Player::Interpolate(float tick){

//    std::cout << tick << std::endl;

    float x = Previous.Position.x *(1-tick) + Current.Position.x*tick;
    float y = Previous.Position.y *(1-tick) + Current.Position.y*tick;
    

    if(SPEED.x != 0 || SPEED.y != 0)
        PlayerSprite.setPosition(x, y);
}