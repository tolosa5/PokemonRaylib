#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include "src/components/MovementComponent.hpp"
#include "src/components/AnimationComponent.hpp"
#include "src/components/Sprite.hpp"
#include "src/utils/Utils.hpp"

enum TagsEnum
{
    PLAYER,
    INTERACTABLE,
};

class Entity
{

protected:

    Sprite sprite;

    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    TagsEnum tag;

public:
    Entity();
    virtual ~Entity();

    void SetSpriteTexture(Texture2D& texture);
    void CreateMovementComponent(const float maxSpeed);
    void CreateAnimationComponent();

    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void SetPosition(const Vector2 position);
    virtual void Move(const Vector2 direction);
};

#endif