
#pragma once
    
    class eTime {
        public:
            eTime();
            eTime(float sec);
            void setMilisec(int milisec);
            float asSeconds();                      //TIEMPO EN SEGUNDOS
            float asMilliseconds();                 //TIEMPO EN MILISEGUNDOS
            float asMicroseconds();                 //TIEMPO EN MICROSEGUNDOS
            void incrementTime(eTime t);
            void Zero();                            //TENER A 0 EL TIEMPO
        private:
            float _milisecond; 
    };
    