
#include <iostream>

#include "JamEngine.hpp"
#include "AssetManager.hpp"
#include "../ASSETS_IDs.hpp"


AssetManager::AssetManager(){

    uint8_t i = MAX_TEXTURES;
    while(i--){
        TexturesArray[i] = nullptr;
        fontArray[i] = nullptr;
    }

}

AssetManager::~AssetManager(){
    freeAssets();
}

void AssetManager::loadInitialAssets(){
    // loadTexture(LOGO_PNG, "assets/logo.png");
 	// loadTexture(BIPEAL, "assets/bipedal3.png");

	// loadAnimation(AnimBipedal, BIPEAL,7,eTime(200),true);
    loadTexture(PLAYER, "assets/Textures/Player.jpg");
    loadTexture(BLACK_BACKGROUND, "assets/Textures/Black.jpg");
    loadTexture(WHITE_BACKGROUND, "assets/Textures/White.jpg");
    loadTexture(BLACKCUBE, "assets/Textures/Black15x15.jpg");
    loadTexture(WHITECUBE, "assets/Textures/White15x15.jpg");
    loadTexture(POPUP, "assets/Textures/manes.jpg");

}

SDL_Texture* AssetManager::loadTexture(uint8_t ID, const char* TexturePath){
    
    SDL_Surface* imageSurface = IMG_Load(TexturePath);
    TexturesArray[ID] = SDL_CreateTextureFromSurface(JamEngine::Instance()->Renderer, imageSurface);
    if(TexturesArray[ID] == nullptr){
        std::cout << "[!] ERROR cargando textura " << std::endl;
    }
    SDL_FreeSurface(imageSurface);

    return TexturesArray[ID];
}

eFont* AssetManager::loadFont(uint8_t ID, const char* FontPath){
     fontArray[ID] = new eFont(FontPath,10);
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