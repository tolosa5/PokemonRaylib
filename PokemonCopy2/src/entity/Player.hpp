#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include "Entity.hpp"

class Player : public Entity
{
private:
    bool isRunning;

    void InitVariables();
    void InitComponents(Texture2D& texture);

public:
    Player(Texture2D& texture, Vector2 position);
    virtual ~Player();

    void Update(float deltaTime) override;
    void Draw() override;
    void LoadAnimations();
    void Interact();
    void OpenMenu();
    void ToggleRun() { isRunning = !isRunning; }

    MovementComponent* GetMovementComponent() const { 
        return movementComponent; }
};

#endif