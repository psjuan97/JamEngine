#include "Player.hpp"

#include "engineModules/JamEngine.hpp"
#include "ASSETS_IDs.hpp"

#define PlayerAnimation1 0

#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540

#define PLAYER_SPEED 5
#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 8

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

Player::Player(){
    //aSprite.setAnimation(PlayerAnimation1);
    PlayerSprite.setTexture(AssetManager::Instance()->getTexture(PLAYER));
    PlayerSprite.setSize(8, 8);
    PlayerSprite.setPosition(120, 136);

    JamEngine::Instance()->setDrawable_ZIndex(&PlayerSprite, 9);
    
    // EventManager::Instance()->registerEvent(PspCtrlButtons::LEFT, (void *)&Player::MoveLeft );
	// EventManager::Instance()->registerEvent(PspCtrlButtons::UP, (void *)&Player::MoveUp);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::RIGHT, (void *)&Player::MoveRight);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::DOWN, (void *)&Player::MoveDown);

    // Cada tecla tiene asociado un método
    BUTTON_MAPPING[0] = {PspCtrlButtons::CROSS, &Player::Dash};
    BUTTON_MAPPING[1] = {PspCtrlButtons::CIRCLE, &Player::Skill2};

    eventManager = EventManager::Instance();
    Position = PlayerSprite.getPosition();
    Previous.Position = Current.Position = Position;
}

Player::~Player(){

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
}


void Player::CheckMovement(){
    int8_t X_AXIS = eventManager->getButtonState(PspCtrlButtons::RIGHT) - eventManager->getButtonState(PspCtrlButtons::LEFT);
    int8_t Y_AXIS = eventManager->getButtonState(PspCtrlButtons::DOWN) - eventManager->getButtonState(PspCtrlButtons::UP);

    // Check screen bounds:

    /*              Left                                                                Right                               */
    if( (X_AXIS < 0 && (Position.x + SPEED.x) < 0) || (X_AXIS > 0 && (Position.x + SPEED.x + PLAYER_WIDTH) > SCREEN_WIDTH) )
        SPEED.x = 0;
    else
        SPEED.x = PLAYER_SPEED * X_AXIS;

    /*              Top                                                                Bottom                               */
    if( (Y_AXIS < 0 && (Position.y + SPEED.y) < 0) || (Y_AXIS > 0 && (Position.y + SPEED.y + PLAYER_HEIGHT) > SCREEN_HEIGHT) )
        SPEED.y = 0;
    else
        SPEED.y = PLAYER_SPEED * Y_AXIS;
}

void Player::Dash(){

}

void Player::Skill2(){

}


void Player::Interpolate(float tick){

//    std::cout << tick << std::endl;

    float x = Previous.Position.x *(1-tick) + Current.Position.x*tick;
    float y = Previous.Position.y *(1-tick) + Current.Position.y*tick;
    

    if(SPEED.x != 0 || SPEED.y != 0)
        PlayerSprite.setPosition(x, y);
}