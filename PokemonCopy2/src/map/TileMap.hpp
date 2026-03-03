#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "Tile.hpp"
#include "src/utils/Utils.hpp"
#include <iostream>
#include <vector>
#include <fstream>

class TileMap
{
private:
    std::vector<std::vector<std::vector<Tile*>>> map;
    Rectangle paintedRect;
    Texture2D tileTextureSheet;
    Vector2 maxSize; // in tiles
    std::string textureFile;
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;

    void ClearMap();

public:
    TileMap(float gridSize, unsigned width, 
        unsigned layer, std::string textureFile);
    virtual ~TileMap();

    void Update();
    void Draw();

    void AddTile(const unsigned x, const unsigned y, 
        const unsigned z, const Rectangle& sourceRect, 
        const bool collision, const short type);
    void RemoveTile(const unsigned x, 
        const unsigned y, const unsigned z);

    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

    Texture2D* GetTextureSheet() { return &tileTextureSheet; }
};

#endif