#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(Sprite& sprite, 
    Vector2 size, Vector2 offset) 
    : sprite(sprite), offset(offset)
{
    this->collider = 
    { 
        sprite.position.x + offset.x, 
        sprite.position.y + offset.y, 
        size.x, size.y
    };
}

ColliderComponent::~ColliderComponent()
{

}

void ColliderComponent::Update(Vector2 position)
{
    collider.x = position.x + offset.x;
    collider.y = position.y + offset.y;
}

void ColliderComponent::Draw()
{
    DrawRectangleLinesEx(collider, 2, RED);
}

bool ColliderComponent::CheckOverlap(Rectangle otherCollider)
{
    return CheckCollisionRecs(collider, otherCollider);
}