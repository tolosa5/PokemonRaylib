#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include "Entity.hpp"

class Player : public Entity
{
private:
    void InitVariables();
    void InitComponents();

public:
    Player(Texture2D& texture, Vector2 position);
    virtual ~Player();

    void Update(float deltaTime) override;
    void Draw() override;

    MovementComponent* GetMovementComponent() const { return movementComponent; }
};

#endif