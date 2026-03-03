#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include "PokemonSpecies.hpp"

class Pokemon
{
public:
    Pokemon(PokemonSpecies* species = nullptr, int level = 1);
    virtual ~Pokemon();

    PokemonSpecies* species;

    int level;
    int currentHP;

    Stats stats;
    Stats ivs;
    Stats evs;

    std::vector<Move> moves;

    bool isFainted() const
    {
        return currentHP <= 0;
    }

    void CalculateStats();
    int CalculateNonHpStat(int base, int iv, int ev, int level)
    {
        return (((2 * base + iv + (ev / 4)) * level) / 100) + 5;
    }

    int CalculateHpStat(int base, int iv, int ev, int level)
    {
        return (((2 * base + iv + (ev / 4)) * level) / 100) + level + 10;
    }
};

#endif