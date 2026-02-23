#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include "Entity.hpp"

class Player : public Entity
{
private:
    void InitVariables();
    void InitComponents(Texture2D& texture);

public:
    Player(Texture2D& texture, Vector2 position);
    virtual ~Player();

    void Update(float deltaTime) override;
    void Draw() override;
    void LoadAnimations();

    MovementComponent* GetMovementComponent() const { 
        return movementComponent; }
};

#endif