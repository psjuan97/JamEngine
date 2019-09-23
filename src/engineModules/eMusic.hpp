#pragma once
#include <string>

#include <SDL2/SDL_mixer.h>


class eMusic {
public:
    eMusic(const std::string & filename);
    ~eMusic();
    
    bool openFromFile(const std::string & filename);
    void play();
    void stop();
    void pause();
    
    void setVolume(float volume);
        
    
private:

Mix_Music *music = nullptr;

};

