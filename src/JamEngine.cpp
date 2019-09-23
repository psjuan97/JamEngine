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
   // Mix_CloseAudio();
    SDL_Quit();
}

bool JamEngine::Init() {

    #ifdef PSP
            setupExitCallback();
    #endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO ) < 0)
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

    //Initialize SDL_mixer
  /*  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        //printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(2);
    }*/

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
    SDL_RenderPresent(Renderer);
}



void JamEngine::Update(){
    //update inputs?
    //update physics?
}

 bool JamEngine::isOpen(){
     return !exitRequest;
 }



