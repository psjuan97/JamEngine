#ifndef SCORE_S_H
#define SCORE_S_H

#include <cstdint>

class SCORE_S{
    // METHODS
    public:
        static SCORE_S* Instance(){
            static SCORE_S instance;
            return &instance;
        }
        ~SCORE_S();

    private:
        SCORE_S();
        SCORE_S(const SCORE_S& orig);
        void operator=(const SCORE_S& orig);

    // VARIABLES
    public:
        uint32_t SCORE;
};

#endif