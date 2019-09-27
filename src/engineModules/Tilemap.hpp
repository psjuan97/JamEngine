#ifndef TILEMAP_H
#define TILEMAP_H


#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include "Drawable.hpp"


#define TILE_WIDTH  16  
#define TILE_HEIGHT 16


struct TILE {
    // X Coord in Tilesheet
    uint16_t X;

    // Y Coord in Tilesheet
    uint16_t Y;
public:
    TILE(uint16_t _x, uint16_t _y);
};

class Tilemap : public Drawable {
    friend class JamEngine;

    // METHODS
    public:

        Tilemap(SDL_Texture* _Tilesheet);
        Tilemap(const Tilemap& orig);
        void operator=(const Tilemap &orig);
        ~Tilemap();
        
        void loadTilesheet(SDL_Texture* _Tilesheet);
        void loadTileMap(std::string TILEMAP_PATH);
        void setOffset(int X, int Y);
        virtual void Draw();

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

        int X_OFFSET;
        int Y_OFFSET;
        
        uint16_t MAP_WIDTH;
        uint16_t MAP_HEIGHT;
};

#endif