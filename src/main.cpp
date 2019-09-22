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

//Fonts IDs 
#define DEFAULT_FONT 90



#ifdef PSP

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

#define VERS 1 //Talk about this
#define REVS 0
PSP_MODULE_INFO("SDL IS HERE", 0 , VERS, REVS);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(-1 * 1024);




#endif

int main(){

	JamEngine* JAM = JamEngine::Instance();
	AssetManager* Assets = AssetManager::Instance();

	JAM->Init();

	std::cout << TILESHEET+TILESHEET+TILESHEET << std::endl;
    SDL_Texture* T = Assets->loadTexture(LOGO_PNG, "assets/logo.png");
    SDL_Texture* SP = Assets->loadTexture(TILESHEET, "assets/TILED/tilesheet.png");
	eFont* font = Assets->loadFont(DEFAULT_FONT, "assets/DEFAULT.ttf");
	eText::setFont(font);

	eText texto(40,40);

	texto.setString("Hola");


	Tilemap TESTMAP(SP);
	TESTMAP.loadTileMap("assets/BinaryFiles/TEST.map");

	Sprite* HOLI = Assets->getSprite(HOLI_SPRITE);
	HOLI->setTexture(T);
	HOLI->setSize(50, 50); 
	HOLI->setPosition(200, 100);

    

	while(JAM->isOpen()){
		JAM->Clear();

		TESTMAP.Dro();
		HOLI->Dro();
		texto.draw();

		JAM->Dro();

	 // SDL_Delay(5);

	}


JAM->~JamEngine();

}