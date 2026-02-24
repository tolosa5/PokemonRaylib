#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "raylib.h"
#include "src/components/Sprite.hpp"
#include <iostream>


class ColliderComponent
{
private:
    

public:
    Sprite& sprite;
    Rectangle collider;
    Vector2 offset;
    bool solid;
    bool isColliding;

    ColliderComponent(Sprite& sprite, Vector2 size, Vector2 offset = {0, 0});
    virtual ~ColliderComponent();

    void Update(Vector2 position);
    void Draw();
    bool CheckOverlap(Rectangle otherCollider);

    bool IsSolid() const { return solid; }
    bool IsColliding() const { return isColliding; }
};

#endif