#include "BinaryParser.hpp"
#include <iostream>
#include <fstream>
//#include <experimental/filesystem>

template<typename T>
std::istream & MRead(std::istream& _istream, T& value){
    return _istream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void BinaryParser::LoadTilemap(const std::string &BinaryFile, uint16_t* WidthOutput, uint16_t* HeightOutput, std::vector<uint16_t>* TilemapOutput){

    std::ifstream MAP(BinaryFile, std::ios::binary);

    if(!MAP.is_open()){
        std::cout << " Couldn't open " + BinaryFile << '\n';
        return;
    }

    uint16_t w, h;
    MRead(MAP, w);
    MRead(MAP, h);

    *WidthOutput = w;
    *HeightOutput = h;

    uint16_t Size;
    MRead(MAP, Size);

    uint16_t TileID;
    TilemapOutput->reserve(Size);
    for(uint16_t i = 0; i < Size; ++i){
        MRead(MAP, TileID);
        TilemapOutput->push_back(TileID);
    }
}