#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H



#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "eFont.hpp"
#include "eMusic.hpp"
#include "Animation.hpp" 

#define MAX_TEXTURES 255
#define MAX_FONTS 255
#define MAX_MUSICS 255
#define MAX_ANIMATIONS 255

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

        inline eFont* getFont(uint8_t ID) {
            return fontArray[ID];
        };

        inline eMusic* getMusic(uint8_t ID) {
            return musicArray[ID];
        };

        inline Animation* getAnimation(uint8_t ID) {
            return animArray[ID];
        };


        void loadInitialAssets();


        SDL_Texture* loadTexture(uint8_t ID, const char* TexturePath);
        eFont* loadFont(uint8_t ID, const char* FontPath);
        Animation* loadAnimation(uint8_t animID, uint8_t textureID, uint8_t nFrames,  eTime const& duration, bool looping);
        eMusic* loadMusic(uint8_t ID, const char* MusicPath);
        eMusic* loadMusic(uint8_t ID, const char* MusicPath, const uint8_t loop, int volume);

        void freeTextures();
        void freeFonts();
        void freeAssets();
        
    private:

        AssetManager();
        AssetManager(const AssetManager& orig) = delete;
        void operator=(const AssetManager &orig) = delete;



    // VARIABLES
    public:

    private:
        SDL_Texture* TexturesArray[MAX_TEXTURES];
        eFont* fontArray[MAX_FONTS];
        eMusic* musicArray[MAX_MUSICS];
        Animation* animArray[MAX_ANIMATIONS];

};


#endif