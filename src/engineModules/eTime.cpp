#include "eTime.hpp"

//============================= TIEMPO =============================//
eTime::eTime():_milisecond(0) {}
eTime::eTime(float sec){
    this->_milisecond = sec * 1000.0f;
}

void eTime::setMilisec(int _milisecond){
    this->_milisecond = (float)_milisecond;
}

float eTime::asSeconds        ()  {   
    return this->_milisecond / 1000 ;

}
float eTime::asMilliseconds   ()  {   
    return this->_milisecond;
}
float eTime::asMicroseconds   ()  {  
     return this->_milisecond * 1000;
}
void eTime::Zero              ()  {   
    this->_milisecond = 0;
}
void eTime::incrementTime(eTime t){ 
    this->_milisecond += t.asMilliseconds();
}



