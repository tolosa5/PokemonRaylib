#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "Tile.hpp"
#include "src/utils/Utils.hpp"
#include <iostream>
#include <vector>

class TileMap
{
private:
    std::vector<std::vector<std::vector<Tile*>>> map;
    Rectangle paintedRect;
    Texture2D tileTextureSheet;
    Vector2 maxSize; // in tiles
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;

public:
    TileMap(float gridSize, unsigned width, unsigned layer);
    virtual ~TileMap();

    void Update();
    void Draw();

    void AddTile(const unsigned x, const unsigned y, 
        const unsigned z, const Rectangle& sourceRect);
    void RemoveTile(const unsigned x, 
        const unsigned y, const unsigned z);

    unsigned GetSheetColumns(float tileWidth) const;
    unsigned GetSheetRows(float tileHeight) const;

    Texture2D* GetTextureSheet() { return &tileTextureSheet; }
};

#endif