#include "MapParser.hpp"
#include <iostream>
#include <vector>

#include "BinaryHelper.hpp"
#include "FILE_DIRECTORIES.hpp"
#include <fstream>
#include <cstdint>

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

    tinyxml2::XMLDocument map_doc;

    if(map_doc.LoadFile(Input.c_str()) != 0){
        std::cout << " Couldn't open " << Input << '\n';
        return;
    }

    //CONSIGO EL ANCHO Y EL ALTO DEL NODO (Número de casillas del mapa)
    tinyxml2::XMLElement *map;
    map = map_doc.FirstChildElement("map");
    map->QueryIntAttribute("width", &map_width);
    map->QueryIntAttribute("height", &map_height);


    //CONSIGO EL TEXTO
    tinyxml2::XMLElement* data = map->FirstChildElement("layer")->FirstChildElement("data");


    for(tinyxml2::XMLElement* id = data->FirstChildElement("tile"); id != nullptr; id = id->NextSiblingElement("tile")){

        int _I;
        if(id->QueryIntAttribute("gid", &_I) == tinyxml2::XML_NO_ATTRIBUTE){
            _I = 0;
        }

        Tiles.emplace_back(_I - 1);
    }
    


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
