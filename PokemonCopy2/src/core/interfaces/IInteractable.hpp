#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "ICollidable.hpp"

class IInteractable : public ICollidable
{
protected:
    bool interactable = true;

public:
    virtual void Interact() = 0;

    bool IsInteractable() const { return interactable; }
};

#endif