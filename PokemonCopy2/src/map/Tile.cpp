#include "Tile.hpp"

Tile::Tile(float x, float y, float gridSizeF)
{
    shape.height = gridSizeF;
    shape.width = gridSizeF;
    shape.x = x;
    shape.y = y;
}

Tile::~Tile()
{

}

void Tile::Update()
{

}

void Tile::Draw()
{
    DrawRectangleRec(shape, WHITE);
}