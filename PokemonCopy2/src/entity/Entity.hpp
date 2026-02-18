#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

enum TagsEnum
{
    PLAYER,
    INTERACTABLE,
};

class Entity
{
private:
    Texture2D image;

protected:
    float speed;
    TagsEnum tag;

public:
    Entity(Vector2 position, TagsEnum tag);
    virtual ~Entity();

    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void Move(const Vector2 direction);

    Vector2 position;
};

#endif