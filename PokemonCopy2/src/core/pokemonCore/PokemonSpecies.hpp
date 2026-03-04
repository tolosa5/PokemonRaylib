#ifndef POKEMONSPECIES_HPP
#define POKEMONSPECIES_HPP

#include <string>
#include <vector>
#include "TypeSystem.hpp"
#include "Stats.hpp"
#include "Move.hpp"
#include "MoveData.hpp"

class PokemonSpecies
{
public:
    int id;
    std::string name;
    Type type1;
    Type type2;
    Stats baseStats;
    std::vector<MoveData> learnableMoves;
};

#endif