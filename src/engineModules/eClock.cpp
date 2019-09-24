#include "eClock.hpp"
#include "../JamEngine.hpp"
//============================= RELOJ =============================//
eClock::eClock() {
    this->start.Zero();
}

eTime eClock::restart() { 
    eTime timeToReturn;
    timeToReturn.setMilisec(JamEngine::Instance()->getTicks() - (int)this->start.asMilliseconds());
    start.setMilisec(JamEngine::Instance()->getTicks());
    return timeToReturn;
}

eTime eClock::getElapsedTime() { 
    return eTime(JamEngine::Instance()->getTicks() - (int)this->start.asMilliseconds());
}

