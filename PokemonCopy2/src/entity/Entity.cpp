#include "Entity.hpp"

Entity::Entity(Vector2 position)
{
    this->position = position;
    speed = 2.0f;
}

Entity::~Entity()
{
    UnloadTexture(image);
}

void Entity::Update()
{
    
}

void Entity::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void Entity::Move(const Vector2 direction)
{
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}