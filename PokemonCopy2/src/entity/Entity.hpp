#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include "src/components/MovementComponent.hpp"
#include "src/components/AnimationComponent.hpp"
#include "src/components/ColliderComponent.hpp"
#include "src/components/Sprite.hpp"
#include "src/utils/AnimationSystem.hpp"
#include "src/utils/Utils.hpp"


class Entity
{

protected:

    Sprite sprite;

    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    ColliderComponent* colliderComponent;

public:
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
};

#endif