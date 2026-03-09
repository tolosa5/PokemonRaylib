#ifndef BATTLEUNIT_HPP
#define BATTLEUNIT_HPP

#include "raylib.h"
#include "src/core/pokemonCore/Pokemon.hpp"
#include "src/components/Sprite.hpp"

class BattleUnit
{
private:
    Pokemon* pokemon;
    bool isPlayer;

    Rectangle rect;

    Vector2 startPosition;
    Vector2 battlePosition;
    Vector2 currentPosition;

public:
    BattleUnit();
    ~BattleUnit();

    void SetUp(Pokemon* pokemon, bool isPlayer);
    void BattleStart();
    void Draw();

    void PerformMoveAnimation(Move& move);

    Pokemon* GetPokemon() const { return pokemon; }
};

#endif