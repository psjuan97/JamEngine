#include "StateMachine.hpp"

StateMachine::StateMachine()
:QueriedState(nullptr)
{
    CurrentUpd = &StateMachine::ProcessChanges;
}

StateMachine::~StateMachine(){
    if(CurrentState){
        delete CurrentState;
    }
}


void StateMachine::setState(State* newState){
    if(newState){
        QueriedState = newState;
        CurrentUpd = &StateMachine::ProcessChanges;
    }
}

void StateMachine::Update(){
    (this->*CurrentUpd)();
}

void StateMachine::UpdateCurrentState(){
    CurrentState->Update();
}

void StateMachine::ProcessChanges(){
    if(CurrentState){
        CurrentState->Exit();
        delete CurrentState;
    }
    
    CurrentState = QueriedState;
    CurrentState->Init();
    QueriedState = nullptr;
    //CurrentState->Update();
    CurrentUpd = &StateMachine::UpdateCurrentState;
}

