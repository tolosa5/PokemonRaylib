#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include "TileMap.hpp"
#include <fstream>

class MapLoader
{
public:
    MapLoader();
    virtual ~MapLoader();

    static TileMap loadMap(const std::string& filename);
};

#endif