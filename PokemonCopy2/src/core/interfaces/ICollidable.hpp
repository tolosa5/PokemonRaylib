#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "src/components/ColliderComponent.hpp"

class ICollidable
{
public:
    ColliderComponent* colliderComponent;
    ColliderComponent* GetCollider() const { return colliderComponent; }
};

#endif