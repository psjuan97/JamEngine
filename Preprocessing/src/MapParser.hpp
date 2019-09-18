#ifndef _MAPPARSER_H
#define _MAPPARSER_H

#include "tinyxml2.h"
#include <string>

struct MapParser{
    static void LoadMap(const std::string &Input, const std::string &Output);
};

#endif