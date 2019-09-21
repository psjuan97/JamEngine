#include "JamEngine.hpp"


JamEngine::JamEngine()
:Renderer(nullptr),
 Window(nullptr)
{

}

JamEngine::~JamEngine(){
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

bool JamEngine::Init() {

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

    // el render se ha creado?
    if (!Renderer) return false;

    Sprite::setRenderer(Renderer);
    Tilemap::setRenderer(Renderer);

    return true;
}

void JamEngine::Clear(){
    SDL_RenderClear(Renderer);
}

void JamEngine::Dro(){
    SDL_RenderPresent(Renderer);
}
