#include "eClock.hpp"
#include "JamEngine.hpp"
//============================= RELOJ =============================//
eClock::eClock() {
    this->start.Zero();
}

eTime eClock::restart() { 
    eTime timeToReturn;
    int ticks = JamEngine::Instance()->getTicks() ;
    timeToReturn.setMilisec(ticks - this->start.asMilliseconds());
    start.setMilisec(ticks);
    return timeToReturn;
}

eTime eClock::getElapsedTime() { 
    return eTime(JamEngine::Instance()->getTicks() - this->start.asMilliseconds());
}

