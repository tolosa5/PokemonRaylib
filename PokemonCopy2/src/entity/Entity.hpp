#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"

class Entity
{
private:
    Texture2D image;

protected:
    float speed;

public:
    Entity(Vector2 position);
    virtual ~Entity();

    virtual void Update();
    virtual void Draw();
    virtual void Move(const Vector2 direction);

    Vector2 position;
};

#endif