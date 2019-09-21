#ifndef JAMENGINE_H
#define JAM_H

#include "Sprite.hpp"
#include "Tilemap.hpp"

#include <SDL2/SDL.h>

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
        void Clear();
        void Dro();

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