#pragma once
#include "../math/Vector2.hpp"

class eView {
    friend class JamEngine;
    public:
        eView(int size_x, int size_y);        //CONSTRUCTOR
        
        void zoom(int z);                         //ZOOM A LA VISTA
        void setCenter(int x, int y);           //CENTRO DE LA VISTA
        math::Vector2<int> getCenter();            //CENTRO DE LA VISTA
        void move(int x, int y);                //MOVER LA VISTA  
        void setSize(int x, int y);
        int getZoom();
    private:
        bool hasTarget_;
        int targetX;
        int targetY;
        int _zoom;
        int center_pos_x, center_pos_y, size_x, size_y;
};