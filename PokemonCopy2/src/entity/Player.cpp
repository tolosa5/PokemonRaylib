#include "Player.hpp"

void Player::InitVariables()
{
    
}

void Player::InitComponents()
{
    CreateMovementComponent(80.0f);
}

Player::Player(Texture2D& texture, Vector2 position)
{
    InitVariables();
    InitComponents();
    SetSpriteTexture(texture);
    SetPosition(position);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    Entity::Update(deltaTime);
}

void Player::Draw()
{
    Entity::Draw();
}