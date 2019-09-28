#ifndef SCORE_H
#define SCORE_H

#include "engineModules/StateMachine.hpp"
#include "engineModules/eText.hpp"

class sScore : public State {
    // METHODS
    public:
        sScore();
        sScore(const sScore& orig);
        ~sScore();

        virtual void Init();
        virtual void Update();
        virtual void Exit();

    // VARIABLES
    private:
        eText FINAL_SCORE;
        eText AGAIN;
};

#endif