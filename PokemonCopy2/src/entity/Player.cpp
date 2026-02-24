#include "Player.hpp"

void Player::InitVariables()
{
    
}

void Player::InitComponents(Texture2D& texture)
{
    CreateMovementComponent(200.0f);
    CreateAnimationComponent(texture, 16, 16);
    CreateColliderComponent(sprite);
}

Player::Player(Texture2D& texture, Vector2 position)
{
    InitVariables();
    SetSpriteTexture(texture);
    InitComponents(texture);
    SetPosition(position);

    LoadAnimations();
    animationComponent->Play("IDLE_DOWN");
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    Entity::Update(deltaTime);
    
    if (movementComponent->IsIdle())
    {
        if (movementComponent->lastDirection.x == 0 && 
            movementComponent->lastDirection.y == 1)
            animationComponent->Play("IDLE_DOWN");

        else if (movementComponent->lastDirection.x == 0 && 
            movementComponent->lastDirection.y == -1)
            animationComponent->Play("IDLE_UP");

        else if (movementComponent->lastDirection.x == -1 && 
            movementComponent->lastDirection.y == 0)
            animationComponent->Play("IDLE_LEFT");

        else if (movementComponent->lastDirection.x == 1 && 
            movementComponent->lastDirection.y == 0)
            animationComponent->Play("IDLE_RIGHT");
    }
    
    else
    {
        if (movementComponent->direction.x == 0 && 
            movementComponent->direction.y == 1)
            animationComponent->Play("WALK_DOWN");

        else if (movementComponent->direction.x == 0 && 
            movementComponent->direction.y == -1)
            animationComponent->Play("WALK_UP");

        else if (movementComponent->direction.x == -1 && 
            movementComponent->direction.y == 0)
            animationComponent->Play("WALK_LEFT");

        else if (movementComponent->direction.x == 1 && 
            movementComponent->direction.y == 0)
            animationComponent->Play("WALK_RIGHT");
    }
}

void Player::Draw()
{
    Entity::Draw();
}

void Player::LoadAnimations()
{
    animationComponent->AddAnimation("WALK_DOWN", 0, 3, 0.2f);
    animationComponent->AddAnimation("WALK_UP", 1, 3, 0.2f);
    animationComponent->AddAnimation("WALK_LEFT", 2, 2, 0.2f);
    animationComponent->AddAnimation("WALK_RIGHT", 3, 2, 0.2f);

    animationComponent->AddAnimation("IDLE_DOWN", 4, 1, 0.2f);
    animationComponent->AddAnimation("IDLE_UP", 5, 1, 0.2f);
    animationComponent->AddAnimation("IDLE_LEFT", 6, 1, 0.2f);
    animationComponent->AddAnimation("IDLE_RIGHT", 7, 1, 0.2f);
}

void Player::Interact()
{
}

void Player::OpenMenu()
{
}