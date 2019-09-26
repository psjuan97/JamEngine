#include "MapParser.hpp"
#include <iostream>
#include <vector>

#include "BinaryHelper.hpp"
#include "FILE_DIRECTORIES.hpp"
#include <fstream>
#include <cstdint>
#include "Tmx.h"

void MapParser::LoadMap(const std::string &Input, const std::string &Output){

    int map_width;
    int map_height;

    struct tile{
        tile():tile(0,0,0){}
        tile(uint16_t _id, uint16_t _x = 0, uint16_t _y = 0)
        :id(_id), x(_x), y(_y)
        {};
        uint16_t id;
        uint16_t x;
        uint16_t y;
    };

    std::vector<tile> Tiles;

    Tmx::Map *map = new Tmx::Map();

    map->ParseFile(Input.c_str());

    //CONSIGO EL ANCHO Y EL ALTO DEL NODO (Número de casillas del mapa)

	map_width = map->GetWidth();
	map_height = map->GetHeight();

	printf("Width: %d\n", map_width);
	printf("Height: %d\n", map_height);
	printf("Tile Width: %d\n", map->GetTileWidth());
	printf("Tile Height: %d\n", map->GetTileHeight());


    const Tmx::TileLayer *tileLayer = map->GetTileLayer(0);

    for (int y = 0; y < tileLayer->GetHeight(); ++y)
    {
        for (int x = 0; x < tileLayer->GetWidth(); ++x)
        {
            if (tileLayer->GetTileTilesetIndex(x, y) == -1)
            {
                printf("........    ");
            }
            else
            {
                Tiles.emplace_back(tileLayer->GetTileGid(x, y) - 1);
            }
        }

        //printf("\n");
    }
        
    delete map;


    std::ofstream MAP(MAP_OUPUT_DIR+Output+".map", std::ios::binary);

    uint16_t M_Width  = static_cast<uint16_t>(map_width);
    uint16_t M_Height = static_cast<uint16_t>(map_height);

    MWrite(MAP, M_Width);
    MWrite(MAP, M_Height);

    uint16_t Size = Tiles.size();
    MWrite(MAP, Size);

    //std::cout << "SIZE " << Size << '\n';

    for(uint16_t i = 0; i < Tiles.size(); ++i){
        MWrite(MAP, Tiles[i].id);
        //MWrite(MAP, Tiles[i].x);
        //MWrite(MAP, Tiles[i].y);
    }

    std::cout << "  -NODO: " << Input << " | " << map_width << " x " << map_height << '\n';
    
};
