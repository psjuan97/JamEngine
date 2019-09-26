#include "JamEngine.hpp"

static int exitRequest = 0;


#ifdef PSP

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

////////////////////////////////////////////
////                                    ////
////           PSP ROUTINES             ////
////////////////////////////////////////////


int isRunning() {
  return !exitRequest;
}
int exitCallback(int arg1, int arg2, void *common) {
  exitRequest = 1;
  return 0;
}

int callbackThread(SceSize args, void *argp) {
  int callbackID;
  callbackID = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
  sceKernelRegisterExitCallback(callbackID);
  sceKernelSleepThreadCB();
  return 0;
}
int setupExitCallback() {
  int threadID = 0;
  threadID = sceKernelCreateThread("Callback Update Thread",
    callbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
  if(threadID >= 0) {
    sceKernelStartThread(threadID, 0, 0);
  }
  return threadID;
}

#endif
/////////////////////////////////////////////////
////////////////////////////////////////////////


JamEngine::JamEngine()
:Renderer(nullptr),
 Window(nullptr)
{

}


JamEngine::~JamEngine(){
    SDL_DestroyWindow(Window);
    TTF_Quit();
    SDL_Quit();
}

bool JamEngine::Init() {

    #ifdef PSP
            setupExitCallback();
    #endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
        return false;
    

    Window = SDL_CreateWindow(
                "JamEngine",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
            );

    if (!Window) return false;

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);


     	
    if(TTF_Init() == -1) {
      //  printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }


    // el render se ha creado?
    if (!Renderer) return false;

    Sprite::setRenderer(Renderer);
    Tilemap::setRenderer(Renderer);
    eText::setRenderer(Renderer);

    return true;
}


void JamEngine::drawTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst){
    SDL_RenderCopy(Renderer, texture, src, dst);
}



void JamEngine::Clear(){
    SDL_RenderClear(Renderer);
}

void JamEngine::Dro(){
    uint16_t i = 0;
    while(i < Z_INDEX_LEVELS * DRAWABLES_PER_LEVEL){
        Drawable* Current = DRAWABLEPOOL[i];
        if(Current) Current->Draw();
        ++i;
    }
    SDL_RenderPresent(Renderer);
}



void JamEngine::Update(){
    //update inputs?
    //update physics?
}

bool JamEngine::isOpen(){
    return !exitRequest;
}



//DRAWABLEPOOL
void JamEngine::setDrawable_ZIndex(Drawable* D, uint8_t Z_Index){
    uint8_t Position = CurrentMaxZIndexID[Z_Index]++;
    if(Position > DRAWABLES_PER_LEVEL - 1){
        CurrentMaxZIndexID[Z_Index] = 0;
        Position = 0;
    }
    setDrawable_ZIndex(D, Z_Index, Position);
}

void JamEngine::setDrawable_ZIndex(Drawable* D, uint8_t Z_Index, uint8_t Position){
    DRAWABLEPOOL[Z_Index*DRAWABLES_PER_LEVEL + Position] = D;
}

void JamEngine::clearAllDrawables(){

    uint16_t i = 0;
    while(i < Z_INDEX_LEVELS * DRAWABLES_PER_LEVEL){
        DRAWABLEPOOL[i] = nullptr;
        ++i;
    }

    i = 0;
    while(i < Z_INDEX_LEVELS){
        CurrentMaxZIndexID[i] = 0;
        ++i;
    }

}

void JamEngine::clearZLevel(uint8_t Z_Level){
    uint16_t i = 0;
    uint16_t LEVEL = Z_Level * DRAWABLES_PER_LEVEL;
    while(i < DRAWABLES_PER_LEVEL){
        DRAWABLEPOOL[LEVEL + i] = nullptr;
        ++i;
    }
    CurrentMaxZIndexID[Z_Level] = 0;
}


// Debug
/*
#include <iostream>

void JamEngine::printDrawablepool(){
    std::cout << "POOL: " << Z_INDEX_LEVELS << " x " << DRAWABLES_PER_LEVEL << '\n';
    for(uint8_t i = 0; i < Z_INDEX_LEVELS; ++i){
        for(uint8_t j = 0; j < DRAWABLES_PER_LEVEL; ++j){
            std::cout << DRAWABLEPOOL[i*DRAWABLES_PER_LEVEL + j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "POOL PRINTED ===========" << '\n' << '\n';
}
*/