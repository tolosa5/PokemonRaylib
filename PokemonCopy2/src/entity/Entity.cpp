#include "Entity.hpp"

Entity::Entity(Vector2 position, TagsEnum tag)
{
    this->position = position;
    this->tag = tag;
    speed = 2.0f;
}

Entity::~Entity()
{
    
}

void Entity::Update(float deltaTime)
{
    
}

void Entity::Draw()
{
    DrawRectangle((int)position.x, (int)position.y, 32, 32, RED);
}

void Entity::Move(const Vector2 direction)
{
    position.x += direction.x * speed * GetFrameTime();
    position.y += direction.y * speed * GetFrameTime();
}