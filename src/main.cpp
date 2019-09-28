#include "engineModules/JamEngine.hpp"
#include "engineModules/AssetManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "engineModules/Tilemap.hpp"


#include "engineModules/audio.h" // Pruebas audio
#include "engineModules/EventManager.hpp"
#include "engineModules/eClock.hpp"

#include "engineModules/AnimatedSprite.hpp"
#include "Game.hpp"

#include "ASSETS_IDs.hpp"



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

#define BUTTON_DOWN SDL_JOYBUTTONDOWN
#define BUTTON_UP 1540



int main(){

	JamEngine* JAM = JamEngine::Instance();
	JAM->Init();

	AssetManager* Assets = AssetManager::Instance();
	Assets->loadInitialAssets();

	Game THE_GAME;


	eText::setFont(Assets->getFont(DEFAULT_FONT));
	eText texto(40,40);
	texto.setString("Ejmplo de texto");

	Tilemap TESTMAP(Assets->getTexture(TILESHEET));
	TESTMAP.loadTileMap("assets/BinaryFiles/TEST.map");

	//////////////////////////
	// Prueba musica
	//////////////////////////
	 eMusic* musica = Assets->loadMusic(SAMPLE_MUSIC, "assets/8-bitDetective.wav");
	 musica->playAsSound();
	

    JAM->setDrawable_ZIndex(&TESTMAP, 0);
    JAM->setDrawable_ZIndex(&texto, 3);

    
    while(JAM->isOpen()){
		JAM->Clear();
		
		EventManager::Instance()->launch();
    	
		THE_GAME.Update();

		JAM->Dro();
        // SDL_Delay(5);
	}

 	

//JAM->~JamEngine();

}