#ifndef TILE_HPP
#define TILE_HPP

#include "raylib.h"

class Tile
{
protected:
    Rectangle shape;
    Texture2D texture;

public:
    Tile(float x, float y, float gridSizeF);
    virtual ~Tile();

    void Update();
    void Draw();
};

#endif