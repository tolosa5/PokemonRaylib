#include "Tile.hpp"

Tile::Tile(unsigned gridX, unsigned gridY, float gridSizeF, const Texture2D& tileTextureSheet, 
    const Rectangle& sourceRect, bool collision, short type)
{
    shape.height = gridSizeF;
    shape.width = gridSizeF;
    texture = tileTextureSheet;
    this->sourceRect = sourceRect;
    shape.x = gridX * gridSizeF;
    shape.y = gridY * gridSizeF;
    //shape = sourceRect;

    this->collision = collision;
    this->type = type;
}

Tile::~Tile()
{

}

const std::string Tile::GetAsString() const
{
    std::stringstream ss;

    ss << sourceRect.x << " " << sourceRect.y << " " << 
        collision << " " << type;

    return ss.str();
}

void Tile::Update()
{

}

void Tile::Draw()
{
    //DrawTextureRec(texture, shape, Vector2{ shape.x, shape.y }, WHITE);
    DrawTexturePro(texture, sourceRect, shape, Vector2{0, 0}, 0.0f, WHITE);
}