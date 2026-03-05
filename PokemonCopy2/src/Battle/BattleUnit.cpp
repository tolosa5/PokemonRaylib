#include "BattleUnit.hpp"

BattleUnit::BattleUnit()
    : pokemon(nullptr), isPlayer(false), startPosition({0.0f, 0.0f}),
      battlePosition({0.0f, 0.0f}), currentPosition({0.0f, 0.0f})
{
}

BattleUnit::~BattleUnit() = default;

void BattleUnit::SetUp(Pokemon* pokemon, bool isPlayer)
{
    this->pokemon = pokemon;
    this->isPlayer = isPlayer;

    // Placeholder positions until battle layout logic is added.
    startPosition = isPlayer ? Vector2{80.0f, 260.0f} : Vector2{520.0f, 80.0f};
    battlePosition = startPosition;
    currentPosition = startPosition;
}

void BattleUnit::BattleStart()
{
    currentPosition = battlePosition;
}
