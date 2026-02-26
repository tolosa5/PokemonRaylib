#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "Tile.hpp"
#include "src/utils/Utils.hpp"
#include <vector>

class TileMap
{
private:
    std::vector<std::vector<std::vector<Tile*>>> map;
    Vector2 maxSize; // in tiles
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;

public:
    TileMap(float gridSize, unsigned width, unsigned height);
    virtual ~TileMap();

    void Update();
    void Draw();

    void AddTile(const unsigned x, const unsigned y, const unsigned z);
    void RemoveTile(const unsigned x, const unsigned y, const unsigned z);

    bool IsSolid(Vector2 pos);
    bool IsTallGrass(Vector2 pos);
};

#endif