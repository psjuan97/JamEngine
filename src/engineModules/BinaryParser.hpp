#ifndef _BINARYPARSER_H
#define _BINARYPARSER_H

#include <vector>
#include <string>

namespace BinaryParser{

    void LoadTilemap(const std::string &BinaryFile, uint16_t* WidthOutput, uint16_t* HeightOutput, std::vector<uint16_t>* TilemapOutput);

};

#endif