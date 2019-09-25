#include "eMusic.hpp"


eMusic::eMusic():sound(nullptr),soundVolume(0)
{}

eMusic::eMusic(const char* filename, uint8_t loop, int volume)
:eMusic()
{
    if(!openFromFile(filename, loop, volume)){
        printf("Error al abrir el fichero %s", filename);
    }
}


eMusic::eMusic(const std::string& filename, uint8_t loop, int volume)
:eMusic()
{
	eMusic(filename.c_str(), loop, volume);
}

eMusic::~eMusic(){
	freeAudio(sound);
}

bool eMusic::openFromFile(const char* filename, uint8_t loop, int volume){
	sound = createAudio(filename, loop, volume);

	soundVolume = volume;

	return bool(sound);
}

bool eMusic::openFromFile(const std::string& filename, uint8_t loop, int volume){
	return openFromFile(filename.c_str(),loop,volume);
}

void eMusic::playAsSound(){
    playSoundFromMemory(sound,soundVolume);
}

void eMusic::playAsMusic(){
    playMusicFromMemory(sound,soundVolume);
}