#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include "src/components/MovementComponent.hpp"
#include "src/components/AnimationComponent.hpp"
#include "src/components/Sprite.hpp"
#include "src/utils/AnimationSystem.hpp"
#include "src/utils/Event.hpp"
#include "src/utils/Utils.hpp"
#include "src/core/interfaces/ICollidable.hpp"


class Entity : public ICollidable
{

protected:

    Sprite sprite;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;

public:
    //position, target position, entity
    Event<Vector2, Vector2, Entity*> onEntityMove; 

    Entity();
    virtual ~Entity();

    void SetSpriteTexture(Texture2D& texture);
    void CreateMovementComponent(const float maxSpeed);
    void CreateAnimationComponent(Texture2D& textureSheet, 
        int frameWidth, int frameHeight);
    void CreateColliderComponent(Sprite& sprite);

    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void SetPosition(const Vector2 position);
    virtual void Move(const Vector2 direction);
    void SetCanMove(bool canMove) { movementComponent->moving = canMove; }
};

#endif