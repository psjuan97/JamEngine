#pragma once

#include "eTime.hpp"
  
  class eClock {
        public:
            eClock();
            
            eTime restart();          //REINICIAR EL RELOJ
            eTime getElapsedTime();   //TIEMPO SIN REINICIAR EL RELOJ
        private:
            eTime start;
    };
    