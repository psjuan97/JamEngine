#include "Interpolable_Object.hpp"

void Interpolable_Object::savePreviousState(){
    Previous = Current;    
}

void Interpolable_Object::saveCurrentState(){
    Current.Position = Position;
}