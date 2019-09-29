#ifndef JAMENGINE_H
#define JAMENGINE_H

#include "Sprite.hpp"
#include "Tilemap.hpp"
#include "eText.hpp"
#include "eView.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Drawable.hpp"

#include "audio.h" // Audio engine

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#include <sstream>

template<typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
#define Z_INDEX_LEVELS 11
#define DRAWABLES_PER_LEVEL 20


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
        int getTicks();


        void drawTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst);

        //CAMARA
        void setView(eView v);
        void moveView(int x, int y);
        void setDrawable_ZIndex(Drawable* D, uint8_t Z_Index);
        void setDrawable_ZIndex(Drawable* D, uint8_t Z_Index, uint8_t Position);
        void clearAllDrawables();
        void clearZLevel(uint8_t Z_Level);
        void setBuzz(bool buzz){
            if(buzz){
                buzzTimer = 10;    
            }

            isBuzz = buzz;

        };
        //void printDrawablepool();

    private:
        JamEngine();
        JamEngine(const JamEngine& orig) = delete;
        void operator=(const JamEngine &orig) = delete;



    
    private:
        Drawable* DRAWABLEPOOL[Z_INDEX_LEVELS*DRAWABLES_PER_LEVEL];
        uint8_t CurrentMaxZIndexID[Z_INDEX_LEVELS];

        SDL_Renderer* Renderer;
        SDL_Window* Window;
        SDL_Joystick* GameController ;

        eView camera;

        int buzz;
        bool isBuzz;
        int buzzTimer;
};

#endif