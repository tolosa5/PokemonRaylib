#ifndef INTERACTABLE_NPC_HPP
#define INTERACTABLE_NPC_HPP

#include "Entity.hpp"
#include "src/core/interfaces/IInteractable.hpp"

class InteractableNPC : public Entity, IInteractable
{
    void Interact() override;
};

#endif