#include <iostream>

#include "JamEngine.hpp"
#include "AssetManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Tilemap.hpp"




// Textures IDs
#define TILESHEET 0
#define LOGO_PNG 1


// Sprites IDs
#define HOLI_SPRITE 0

int main(){

	JamEngine* JAM = JamEngine::Instance();
	AssetManager* Assets = AssetManager::Instance();

	JAM->Init();

	std::cout << TILESHEET+TILESHEET+TILESHEET << std::endl;
    SDL_Texture* T = Assets->loadTexture(LOGO_PNG, "assets/logo.png");
    SDL_Texture* SP = Assets->loadTexture(TILESHEET, "assets/TILED/tilesheet.png");
	
	Tilemap TESTMAP(SP);
	TESTMAP.loadTileMap("assets/BinaryFiles/TEST.map");

	Sprite* HOLI = Assets->getSprite(HOLI_SPRITE);
	HOLI->setTexture(T);
	HOLI->setSize(50, 50); 
	HOLI->setPosition(200, 100);

    

	// This is our little game loop.
	for (int i = 0; i < 1000; ++i)
	{
		JAM->Clear();

		TESTMAP.Dro();

		JAM->Dro();

	  SDL_Delay(5);


	}

JAM->~JamEngine();

}