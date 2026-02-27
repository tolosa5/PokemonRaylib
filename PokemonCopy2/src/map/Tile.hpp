#ifndef TILE_HPP
#define TILE_HPP

#include "raylib.h"

class Tile
{
protected:
    Rectangle shape;
    Texture2D texture;
    Rectangle sourceRect;

public:
    Tile(float x, float y, float gridSizeF, 
        const Texture2D& tileTextureSheet, 
        const Rectangle& sourceRect);
    virtual ~Tile();

    void Update();
    void Draw();
};

#endif