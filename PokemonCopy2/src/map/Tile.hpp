#ifndef TILE_HPP
#define TILE_HPP

#include "raylib.h"
#include <string>
#include <sstream>

enum TileType
{
    DEFAULT = 0,
    INTERACTABLE = 1,
    COUNT
};

class Tile
{
protected:
    Rectangle shape;
    Texture2D texture;
    Rectangle sourceRect;

    bool collision;
    short type;

public:
    Tile(unsigned gridX, unsigned gridY, float gridSizeF, 
        const Texture2D& tileTextureSheet, 
        const Rectangle& sourceRect, bool collision = false, 
        short type = TileType::DEFAULT);
    virtual ~Tile();

    void Update();
    void Draw();

    const std::string GetAsString() const;
    const bool HasCollision() const { return collision; }
    const short GetType() const { return type; }
};

#endif