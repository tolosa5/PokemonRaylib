#ifndef POKEBALLTILE_HPP
#define POKEBALLTILE_HPP

#include "Tile.hpp"
#include "src/core/interfaces/IInteractable.hpp"

class PokeballTile : public Tile, IInteractable
{
public:
    void Interact() override;
};

#endif