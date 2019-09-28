#include "Player.hpp"

#include "engineModules/JamEngine.hpp"

#define PlayerAnimation1 0

#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540

#define PLAYER_SPEED 4

Player::Player(){
    aSprite.setAnimation(PlayerAnimation1);
    aSprite.setSize(50, 50);
    aSprite.setPosition(200, 100);

    JamEngine::Instance()->setDrawable_ZIndex(&aSprite, 4);
    
    // EventManager::Instance()->registerEvent(PspCtrlButtons::LEFT, (void *)&Player::MoveLeft );
	// EventManager::Instance()->registerEvent(PspCtrlButtons::UP, (void *)&Player::MoveUp);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::RIGHT, (void *)&Player::MoveRight);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::DOWN, (void *)&Player::MoveDown);

    BUTTON_MAPPING[0] = {PspCtrlButtons::CROSS, &Player::Dash};
    BUTTON_MAPPING[1] = {PspCtrlButtons::CIRCLE, &Player::Skill2};

    eventManager = EventManager::Instance();
    Position = aSprite.getPosition();
    Previous.Position = Current.Position = Position;
}

Player::~Player(){

}

void Player::FixedUpdate(){

    SavePreviousState();

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

    SPEED.x = PLAYER_SPEED * X_AXIS;
    SPEED.y = PLAYER_SPEED * Y_AXIS;
}

void Player::Dash(){

}

void Player::Skill2(){

}


void Player::SavePreviousState(){
    Previous = Current;
}

void Player::SaveCurrentState(){
    Current.Position = Position;
}

void Player::Interpolate(float tick){

    float x = Previous.Position.x *(1-tick) + Current.Position.x*tick;
    float y = Previous.Position.y *(1-tick) + Current.Position.y*tick;

    aSprite.setPosition(x, y);
}