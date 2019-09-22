
#include <iostream>


#include "JamEngine.hpp"
#include "AssetManager.hpp"


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

SDL_Texture* AssetManager::loadTexture(uint8_t ID, const char* TexturePath){
    
    SDL_Surface* imageSurface = IMG_Load(TexturePath);
    TexturesArray[ID] = SDL_CreateTextureFromSurface(JamEngine::Instance()->Renderer, imageSurface);
    SDL_FreeSurface(imageSurface);

    return TexturesArray[ID];
}

eFont* AssetManager::loadFont(uint8_t ID, const char* FontPath){
     fontArray[ID] = new eFont(FontPath,35);
    return  fontArray[ID];
}




void AssetManager::freeAssets(){
    uint8_t i = MAX_TEXTURES;

    while(i--){
        if(!TexturesArray[i])
            SDL_DestroyTexture(TexturesArray[i]);

        TexturesArray[i] = nullptr;

        if(!fontArray[i]){
            fontArray[i]->~eFont();
            fontArray[i] = nullptr;
        }
    }
}
