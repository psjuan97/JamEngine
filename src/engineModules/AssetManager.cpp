
#include <iostream>

#include "JamEngine.hpp"
#include "AssetManager.hpp"
#include "../ASSETS_IDs.hpp"


AssetManager::AssetManager(){

    uint8_t i = MAX_TEXTURES;
    while(i--){
        TexturesArray[i] = nullptr;
        fontArray[i] = nullptr;
        animArray[i] = nullptr;
    }

}

AssetManager::~AssetManager(){
    freeAssets();
}

void AssetManager::loadInitialAssets(){

    

    loadTexture(BLACK_BACKGROUND, "assets/Textures/background_left.png");
    loadTexture(WHITE_BACKGROUND, "assets/Textures/background_right.png");

    loadTexture(COVER, "assets/Textures/background_screen_cover.png");

    loadTexture(POPUP, "assets/Textures/BITCONNEEEEECT.png");
    loadTexture(WARNING, "assets/Textures/Warning.jpg");
    loadTexture(MENUSTART, "assets/Textures/MenuStart.png");
    loadTexture(MENUFIN, "assets/Textures/MenuFin.png");

    loadTexture(SPLASH, "assets/Textures/splash.png");

    ////////////////////
    /////// HERO ///////
    ////////////////////
    loadTexture(PLAYER, "assets/Textures/heroe_anim.png");
    loadAnimation(PlayerAnim,PLAYER,5,eTime(200),true);


    /////////////////////
    //////Enemy Green////
    /////////////////////
    loadTexture(GREENCUBE, "assets/Textures/Cubo_verde_anim.png");
    loadAnimation(GREENENEMYANIM,GREENCUBE,4,eTime(40),true);


    ///////////////////////
    ////// Enemy Pink /////
    ///////////////////////
    loadTexture(PINKCUBE, "assets/Textures/Cubo_rosa_anim.png");
    loadAnimation(PINKENEMYANIM,PINKCUBE,4,eTime(40),true);

}

SDL_Texture* AssetManager::loadTexture(uint8_t ID, const char* TexturePath){
    SDL_Surface* imageSurface = IMG_Load(TexturePath);
    if(imageSurface == nullptr){
        std::cout << "ASDASDASDASDASDASDASDASDASASSSSSSSSSSSSSS" << std::endl;
    }
    TexturesArray[ID] = SDL_CreateTextureFromSurface(JamEngine::Instance()->Renderer, imageSurface);
    if(TexturesArray[ID] == nullptr){
        std::cout << "[!] ERROR cargando textura " << std::endl;
    }
    SDL_FreeSurface(imageSurface);

    return TexturesArray[ID];
}

eFont* AssetManager::loadFont(uint8_t ID, const char* FontPath){
     fontArray[ID] = new eFont(FontPath,20);
    return  fontArray[ID];
}

eMusic* AssetManager::loadMusic(uint8_t ID, const char* MusicPath){
    musicArray[ID] = new eMusic(MusicPath);
    return  musicArray[ID];
}
        

Animation* AssetManager::loadAnimation(uint8_t animID,  uint8_t textureID, uint8_t nFrames, eTime const& duration, bool looping){
    animArray[animID]  = new Animation(textureID,nFrames,duration, looping );
    return animArray[animID];
}



eMusic* AssetManager::loadMusic(uint8_t ID, const char* MusicPath, const uint8_t loop, int volume){
    musicArray[ID] = new eMusic(MusicPath,loop,volume);
    return  musicArray[ID];
}


void AssetManager::freeAssets(){
    
    freeTextures();
    freeFonts();
    
}

void AssetManager::freeTextures(){
    uint8_t i = MAX_TEXTURES;

    while(i--){
        if(TexturesArray[i])
            SDL_DestroyTexture(TexturesArray[i]);

        TexturesArray[i] = nullptr;
    }
}

void AssetManager::freeFonts(){
    uint8_t i = MAX_FONTS;

    while(i--){
        if(fontArray[i]){
            //fontArray[i]->~eFont();
            delete fontArray[i];
            fontArray[i] = nullptr;
        }
    }
}