#include "eMusic.hpp"


eMusic::eMusic(const std::string & filename){
    if(!openFromFile(filename)){
        //printf("Error al abrir el fichero %s", filename.c_str());
    }
}

bool eMusic::openFromFile(const std::string &filename ){
    //music = Mix_LoadMUS(filename.c_str());
     return music != nullptr;
}

void eMusic::play(){
    	//Mix_PlayMusic( music, -1);
}