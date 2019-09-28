#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.hpp"

class StateMachine{
    // METHODS
    public:
        static StateMachine* Instance(){
            static StateMachine instance;
            return &instance;
        }

        ~StateMachine();

        void setState(State* newState);
        void Update();

    private:
        StateMachine();
        StateMachine(const StateMachine& orig) = delete;
        void operator=(const StateMachine& orig) = delete;

        void UpdateCurrentState();
        void ProcessChanges();

    // VARIABLES
    private:

        State* CurrentState;
        State* QueriedState;
        void (StateMachine::*CurrentUpd)();

        
};

#endif