#ifndef JAMENGINE_H
#define JAMENGINE_H

#include "Sprite.hpp"
#include "Tilemap.hpp"
#include "engineModules/eText.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272


class JamEngine {
    friend class AssetManager;
    
    // METHODS
    public:

        static JamEngine* Instance(){
            static JamEngine instance;
            return &instance;
        }

        ~JamEngine();
        
        bool Init();
        bool isOpen();
        void Clear();
        void Dro();
        void Update();


        void drawTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst);
    private:
        JamEngine();
        JamEngine(const JamEngine& orig) = delete;
        void operator=(const JamEngine &orig) = delete;


    // VARIABLES
    public:
    
    private:
        SDL_Renderer* Renderer;
        SDL_Window* Window;

};

#endif