#include "MovementComponent.hpp"

MovementComponent::MovementComponent(Sprite& sprite, float maxSpeed) : 
    sprite(sprite), maxSpeed(maxSpeed)
{
    currentPos = sprite.position;
    targetPos = currentPos;
}

MovementComponent::~MovementComponent()
{
    
}

void MovementComponent::Move(const Vector2 direction)
{
    if (moving)
    {
        Vector2 delta = Vector2Subtract(targetPos, currentPos);
        float distance = Vector2Length(delta);

        if (distance < maxSpeed * GetFrameTime())
        {
            currentPos = targetPos;
            targetPos = currentPos;
            moving = false;
        }
        else
        {
            Vector2 step = Vector2Scale(
                Vector2Normalize(delta), 
                maxSpeed * GetFrameTime());
            currentPos = Vector2Add(currentPos, step);
        }
        
        sprite.Move(currentPos);
    }
}

void MovementComponent::Update()
{
    if (&sprite)
        sprite.position = currentPos;
}