#include "Tilemap.hpp"
#include <iostream>
#include "BinaryParser.hpp"
#include "JamEngine.hpp"
SDL_Renderer* Tilemap::Renderer = nullptr;

Tilemap::Tilemap(SDL_Texture* _Tilesheet)
:Tilesheet(_Tilesheet)
{   
    loadTilesheet(_Tilesheet);
}

Tilemap::Tilemap(const Tilemap& orig){
    TilesheetData = orig.TilesheetData;
    MAP = orig.MAP;

    Tilesheet = orig.Tilesheet;
    Renderer = orig.Renderer;

    X_OFFSET = orig.X_OFFSET;
    Y_OFFSET = orig.Y_OFFSET;
    
    MAP_WIDTH = orig.MAP_WIDTH;
    MAP_HEIGHT = orig.MAP_HEIGHT;
}

void Tilemap::operator=(const Tilemap&orig){
    TilesheetData = orig.TilesheetData;
    MAP = orig.MAP;

    Tilesheet = orig.Tilesheet;
    Renderer = orig.Renderer;

    X_OFFSET = orig.X_OFFSET;
    Y_OFFSET = orig.Y_OFFSET;
    
    MAP_WIDTH = orig.MAP_WIDTH;
    MAP_HEIGHT = orig.MAP_HEIGHT;
}

Tilemap::~Tilemap(){

}

void Tilemap::loadTilesheet(SDL_Texture* _Spritesheet){
    int w, h;
    SDL_QueryTexture(Tilesheet, nullptr, nullptr, &w, &h);

    uint16_t Tilesheet_W = w/TILE_WIDTH;
    uint16_t Tilesheet_H = h/TILE_HEIGHT;

    TilesheetData.reserve(Tilesheet_W*Tilesheet_H);

    uint16_t X_Cont = 0;
    uint16_t Y_Cont = 0;

    for(uint16_t i = 0; i < Tilesheet_H; ++i){
        for(uint16_t j = 0; j < Tilesheet_W; ++j){
            TilesheetData.emplace_back(X_Cont, Y_Cont);
            X_Cont += TILE_WIDTH;
        }

        X_Cont = 0;
        Y_Cont += TILE_HEIGHT;
    }
}

void Tilemap::loadTileMap(std::string TILEMAP_PATH) {
    BinaryParser::LoadTilemap(TILEMAP_PATH, &MAP_WIDTH, &MAP_HEIGHT, &MAP);
}

void Tilemap::setOffset(float X, float Y){
    X_OFFSET = X;
    Y_OFFSET = Y;
}

void Tilemap::Dro(){

    uint16_t X_COORD = X_OFFSET;
    uint16_t Y_COORD = Y_OFFSET;

    SDL_Rect TilesheetSrc;
    SDL_Rect RendererDest;
    TilesheetSrc.w = TILE_WIDTH;
    TilesheetSrc.h = TILE_HEIGHT;
    RendererDest.w = TILE_WIDTH;
    RendererDest.h = TILE_HEIGHT;
    
    for(uint16_t i = 0; i < MAP_HEIGHT; ++i){
        for(uint16_t j = 0; j < MAP_WIDTH; ++j){

            uint16_t ID = MAP[j + i*MAP_WIDTH];
            TilesheetSrc.x = TilesheetData[ID].X; 
            TilesheetSrc.y = TilesheetData[ID].Y;
            //uint16_t ROW = ID/3;
            //TilesheetSrc.x = (ID  - ROW * 3) * TILE_WIDTH; 
            //TilesheetSrc.y = ROW * TILE_HEIGHT;
            RendererDest.x = X_COORD;
            RendererDest.y = Y_COORD;

            X_COORD += TILE_WIDTH;
            JamEngine::Instance()->drawTexture(Tilesheet, &TilesheetSrc, &RendererDest);
        }
        Y_COORD += TILE_HEIGHT;
        X_COORD = X_OFFSET;
    }
}


TILE::TILE(uint16_t _x, uint16_t _y)
:X(_x), Y(_y)
{}