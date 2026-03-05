#include "Entity.hpp"

Entity::Entity()
{
    movementComponent = nullptr;
    animationComponent = nullptr;
    colliderComponent = nullptr;
}

Entity::~Entity()
{
    delete movementComponent;
    delete animationComponent;
    delete colliderComponent;
}

void Entity::SetSpriteTexture(Texture2D& texture)
{
    sprite.texture = texture;
}

void Entity::CreateMovementComponent(const float maxSpeed)
{
    movementComponent = new MovementComponent(sprite, maxSpeed);
}

void Entity::CreateAnimationComponent(
    Texture2D& textureSheet, int frameWidth, int frameHeight)
{
    animationComponent = new AnimationComponent(
        textureSheet, frameWidth, frameHeight);
}

void Entity::CreateColliderComponent(Sprite& sprite)
{
    colliderComponent = new ColliderComponent(
        sprite, {32, 32}, {0, 0});
}

void Entity::Update(float deltaTime)
{
    movementComponent->Update();
    movementComponent->Move(movementComponent->direction);
    sprite.Update(*animationComponent);
    if (colliderComponent)
        colliderComponent->Update(sprite.position);
}

void Entity::Draw()
{
    sprite.Draw(*animationComponent, sprite.position, 2);
    if (colliderComponent)
        colliderComponent->Draw();
}

void Entity::SetPosition(const Vector2 position)
{
    sprite.position = position;
    if (movementComponent)
    {
        movementComponent->currentPos = position;
        movementComponent->targetPos = position;
        movementComponent->moving = false;
    }
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

        onMove.Invoke(sprite.position, movementComponent->targetPos, this);
    }
}