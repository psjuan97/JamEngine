#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H


//#include <cstdint>

#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engineModules/eFont.hpp"
#include "engineModules/eMusic.hpp"

#define MAX_TEXTURES 255
#define MAX_SPRITES 255
#define MAX_FONTS 255
#define MAX_MUSICS 255

class AssetManager{

    // METHODS
    public:

        static AssetManager* Instance(){
            static AssetManager instance;
            return &instance;
        }

        ~AssetManager();

        inline SDL_Texture* getTexture(uint8_t ID) const {
            return TexturesArray[ID];
        };

        inline Sprite* getSprite(uint8_t ID) {
            return &SpritesArray[ID];
        };

        inline eFont* getFont(uint8_t ID) {
            return fontArray[ID];
        };

        inline eMusic* getMusic(uint8_t ID) {
            return musicArray[ID];
        };





        SDL_Texture* loadTexture(uint8_t ID, const char* TexturePath);
        eFont* loadFont(uint8_t ID, const char* FontPath);
        eMusic* loadMusic(uint8_t ID, const char* FontPath);



        void freeAssets();
        
    private:

        AssetManager();
        AssetManager(const AssetManager& orig) = delete;
        void operator=(const AssetManager &orig) = delete;



    // VARIABLES
    public:

    private:
        Sprite SpritesArray[MAX_SPRITES];
        SDL_Texture* TexturesArray[MAX_TEXTURES];
        eFont* fontArray[MAX_FONTS];
        eMusic* musicArray[MAX_MUSICS];
};


#endif