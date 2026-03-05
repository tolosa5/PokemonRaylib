#ifndef POKEBALLTILE_HPP
#define POKEBALLTILE_HPP

#include "Tile.hpp"
#include "src/core/IInteractable.hpp"

class PokeballTile : public Tile, IInteractable
{
    void Interact() override;
};

#endif