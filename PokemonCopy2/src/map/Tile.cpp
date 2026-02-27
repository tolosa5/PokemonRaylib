#include "Tile.hpp"

Tile::Tile(float x, float y, float gridSizeF, const Texture2D& tileTextureSheet, 
    const Rectangle& sourceRect)
{
    shape.height = gridSizeF;
    shape.width = gridSizeF;
    texture = tileTextureSheet;
    this->sourceRect = sourceRect;
    shape.x = x;
    shape.y = y;
    //shape = sourceRect;
}

Tile::~Tile()
{

}

void Tile::Update()
{

}

void Tile::Draw()
{
    //DrawTextureRec(texture, shape, Vector2{ shape.x, shape.y }, WHITE);
    DrawTexturePro(texture, sourceRect, shape, Vector2{0, 0}, 0.0f, WHITE);
}