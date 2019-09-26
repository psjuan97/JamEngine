#include "eView.hpp"

//============================= VISTA =============================//
eView::eView( int size_x, int size_y){ 
    hasTarget_ = false;
    center_pos_x = size_x/2;
    center_pos_y = size_y/2;
    this->size_x =  size_x;
    this->size_y = size_y;
    _zoom = 1;
}

int  eView::getZoom(){
    return _zoom;
}

void eView::zoom      (int z)           {   
    //printf("zoom %f",z);
    
    this->_zoom = z;  
    this->size_x = this->size_x * z;
    this->size_y = this->size_y * z;         
}

void eView::setCenter (int x, int y)  {   
        center_pos_x = x;
        center_pos_y =  y;
}

void eView::move(int x, int y)        {  
    setCenter(center_pos_x + x, center_pos_y + y);
}

void eView::setSize(int x, int y)     {  
    size_x =  x;
    size_y = y;
}

 math::Vector2<int> eView::getCenter  () {
    math::Vector2<int> ret;
    ret.x= this->center_pos_x;
    ret.y = this->center_pos_y;
    
    return ret;
}
