#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>
#include <string>

#define TILE_WIDTH  70
#define TILE_HEIGHT 70


struct TILE {
    // X Coord in Tilesheet
    uint16_t X;

    // Y Coord in Tilesheet
    uint16_t Y;

    TILE(uint16_t _X, uint16_t _Y);
};

class Tilemap{
    friend class JamEngine;

    // METHODS
    public:

        Tilemap(SDL_Texture* _Tilesheet);
        Tilemap(const Tilemap& orig);
        void operator=(const Tilemap &orig);
        ~Tilemap();
        
        void loadTilesheet(SDL_Texture* _Tilesheet);
        void loadTileMap(std::string TILEMAP_PATH);
        void setOffset(float X, float Y);
        void Dro();

    private:

        static inline void setRenderer(SDL_Renderer* R){
            Renderer = R;
        };


    // VARIABLES
    public:
    
    private:
        std::vector<TILE> TilesheetData;
        std::vector<uint16_t> MAP;

        SDL_Texture* Tilesheet;
        static SDL_Renderer* Renderer;

        float X_OFFSET;
        float Y_OFFSET;
        
        uint16_t MAP_WIDTH;
        uint16_t MAP_HEIGHT;
};

#endif