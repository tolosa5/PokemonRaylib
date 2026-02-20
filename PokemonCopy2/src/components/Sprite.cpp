#include "Sprite.hpp"

Sprite::Sprite(Vector2 position, Vector2 scale, float rotation, Color tint)
{
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    this->tint = tint;
}

Sprite::~Sprite()
{
    UnloadTexture(texture);
}

void Sprite::Draw()
{
    DrawTextureEx(texture, position, rotation, scale.x, tint);
}

void Sprite::Update(float deltaTime)
{
    
}

void Sprite::Move(Vector2 targetPosition)
{
    position = targetPosition;
}