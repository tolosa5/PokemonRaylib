#ifndef BATTLEUNIT_HPP
#define BATTLEUNIT_HPP

#include "raylib.h"
#include "src/core/pokemonCore/Pokemon.hpp"

class BattleUnit
{
private:
    Pokemon* pokemon;
    bool isPlayer;

    Vector2 startPosition;
    Vector2 battlePosition;
    Vector2 currentPosition;

public:
    BattleUnit();
    ~BattleUnit();

    void SetUp(Pokemon* pokemon, bool isPlayer);
    void BattleStart();
};

#endif