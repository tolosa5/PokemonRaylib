#include "Entity.hpp"

Entity::Entity()
{
    movementComponent = nullptr;
}

Entity::~Entity()
{
    delete movementComponent;
}

void Entity::SetSpriteTexture(Texture2D& texture)
{
    sprite.texture = texture;
}

void Entity::CreateMovementComponent(const float maxSpeed)
{
    movementComponent = new MovementComponent(sprite, maxSpeed);
}

void Entity::Update(float deltaTime)
{
    sprite.Update(deltaTime);
}

void Entity::Draw()
{
    sprite.Draw();
}

void Entity::SetPosition(const Vector2 position)
{
    sprite.position = position;
}

void Entity::Move(const Vector2 direction)
{
    if (&sprite && movementComponent)
    {
        movementComponent->direction = direction;
        
        movementComponent->targetPos.x = 
            movementComponent->currentPos.x + direction.x * Utils::TILE_SIZE();

        movementComponent->targetPos.y = 
            movementComponent->currentPos.y + direction.y * Utils::TILE_SIZE();

        /*
        // Collision detection with the map
        int tileX = (movementComponent->targetPos.x / Utils::TILE_SIZE());
        int tileY = (movementComponent->targetPos.y / Utils::TILE_SIZE());

        if (map[tileX][tileY] == 1) // Assuming 1 represents a wall or obstacle
            return; // Don't move if the target tile is an obstacle
        */
        
        movementComponent->moving = true;
    }
}