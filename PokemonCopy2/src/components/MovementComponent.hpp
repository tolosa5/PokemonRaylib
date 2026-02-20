#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include "raylib.h"
#include "raymath.h"
#include "src/components/Sprite.hpp"

class MovementComponent
{
private:
    

public:
    MovementComponent(Sprite& sprite, float maxSpeed);
    virtual ~MovementComponent();

    void Move(const Vector2 direction);
    void Update();

    const Vector2& GetDirection() const { return direction; }
    
    float maxSpeed;
    Vector2 direction;
    Vector2 currentPos;
    Vector2 targetPos;
    bool moving = false;

    Sprite& sprite;
};

#endif