#include "Player.hpp"

#include "engineModules/JamEngine.hpp"

#define PlayerAnimation1 0

#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540

#define PLAYER_SPEED 2

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
}

Player::~Player(){

}

void Player::FixedUpdate(){

    CheckMovement();

    // Comprueba si se ha pulsado un botón registrado en el mapping y ejecuta su función asociada
    for(uint8_t i = 0; i < BUTTON_MAPPING.size(); ++i){
        if(eventManager->getAndResetButtonState(BUTTON_MAPPING[i].Button))
            (this->*BUTTON_MAPPING[i].Target)();
    }

    math::Vector2f CurrentPosition = aSprite.getPosition();

    CurrentPosition += SPEED;

    aSprite.setPosition(CurrentPosition.x, CurrentPosition.y);
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


