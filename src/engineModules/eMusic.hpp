#pragma once
#include <string>

#include <iostream>
#include <stdio.h>

#include "audio.h"

#define MAX_VOLUME 	SDL_MIX_MAXVOLUME	// 0 - 128
#define TEST_VOLUME MAX_VOLUME/4.f

class eMusic {
public:
	eMusic();
    eMusic(const std::string& filename,  uint8_t loop = 0, int volume = TEST_VOLUME);
	eMusic(const char* filename, 		 uint8_t loop = 0, int volume = TEST_VOLUME);
    ~eMusic();
    
    bool openFromFile(const char* filename, 		uint8_t loop = 0, int volume = TEST_VOLUME);
    bool openFromFile(const std::string& filename,  uint8_t loop = 0, int volume = TEST_VOLUME);
    
    void playAsSound();
    void playAsMusic();

    // void stop();
    // void pause();
    // void setVolume(float volume);
        
    
private:
	Audio* sound;
	int soundVolume;
};

