#include "engineModules/JamEngine.hpp"
#include "engineModules/AssetManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "engineModules/Tilemap.hpp"


#include "engineModules/audio.h" // Pruebas audio
#include "engineModules/EventManager.hpp"

#include "engineModules/AnimatedSprite.hpp"
#include "Player.hpp"

// Textures IDs
#define TILESHEET 0
#define LOGO_PNG 1
#define BIPEAL 2


// Sprites IDs MAPA 1 
#define HOLI_SPRITE 0


//Fonts IDs 
#define DEFAULT_FONT 0


//MUSIC IDs 
#define SAMPLE_MUSIC 0


//MUSIC IDs 
#define AnimBipedal 0


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

//AnimatedSprite* HOLI = nullptr;

// void moveLeft(uint32_t status){
// 	int velX;
// 	if(status == BUTTON_DOWN){
// 		HOLI->setPosition(HOLI->getPosition().x - 10, HOLI->getPosition().y);


// 	}

// 	return;
// }

// void moveUp(uint32_t status){
// 	int velY;
// 	if(status == BUTTON_DOWN){
// 		HOLI->setPosition(HOLI->getPosition().x, HOLI->getPosition().y - 10);

// 	}
    
// 	return;
// }


// void moveRight(uint32_t status){
// 	int velX;
// 	int ruido = 0;
// 	if(status == BUTTON_DOWN){
// 		HOLI->setPosition(HOLI->getPosition().x + 10, HOLI->getPosition().y);


// 	}

// 	return;
// }


// void moveDown(uint32_t status){
// 	int velY;
// 	if(status == BUTTON_DOWN){
// 		HOLI->setPosition(HOLI->getPosition().x , HOLI->getPosition().y + 10);


// 	}

// 	return;
// }

int main(){

	JamEngine* JAM = JamEngine::Instance();
	AssetManager* Assets = AssetManager::Instance();

	JAM->Init();

	//std::cout << TILESHEET+TILESHEET+TILESHEET << std::endl;
    SDL_Texture* T = Assets->loadTexture(LOGO_PNG, "assets/logo.png");
    SDL_Texture* SP = Assets->loadTexture(TILESHEET, "assets/TILED/tilesheet.png");
 	SDL_Texture* Bipedal = Assets->loadTexture(BIPEAL, "assets/bipedal3.png");

	Assets->loadAnimation(AnimBipedal,BIPEAL,7,eTime(200),true);


	eFont* font = Assets->loadFont(DEFAULT_FONT, "assets/DEFAULT.ttf");
	eText::setFont(font);
	eText texto(40,40);
	texto.setString("Ejmplo de texto");

	Tilemap TESTMAP(SP);
	TESTMAP.loadTileMap("assets/BinaryFiles/TEST.map");

	// HOLI = new AnimatedSprite();
	// HOLI->setAnimation(AnimBipedal);
	// HOLI->setSize(50, 50); 
	// HOLI->setPosition(200, 100);

	//////////////////////////
	// Prueba musica
	//////////////////////////
	 eMusic* musica = Assets->loadMusic(SAMPLE_MUSIC, "assets/8-bitDetective.wav");
	 musica->playAsSound();
	

	// EventManager::Instance()->registerEvent(PspCtrlButtons::LEFT, (void *)moveLeft);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::UP, (void *)moveUp);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::RIGHT, (void *)moveRight);
	// EventManager::Instance()->registerEvent(PspCtrlButtons::DOWN, (void *)moveDown);

    
    JAM->setDrawable_ZIndex(&TESTMAP, 0);
    //JAM->setDrawable_ZIndex(HOLI, 1);
    JAM->setDrawable_ZIndex(&texto, 3);

	Player HERO;
    
    while(JAM->isOpen()){
		JAM->Clear();
    	
		HERO.FixedUpdate();
		EventManager::Instance()->launch();

		JAM->Dro();
        // SDL_Delay(5);
	}

 	

//JAM->~JamEngine();

}