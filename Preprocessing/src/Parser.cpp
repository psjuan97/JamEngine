#include "MapParser.hpp"
//#include <iostream>

#define NODES_ZONE1 16

int main(int argc, char const *argv[]) {

    MapParser::LoadMap("../assets/TILED/TEST.tmx", "TEST");

    return 0;
}
