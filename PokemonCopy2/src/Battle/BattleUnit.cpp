#include "BattleUnit.hpp"

BattleUnit::BattleUnit() : pokemon(nullptr), isPlayer(false), active(true)
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

void BattleUnit::Draw()
{
    if (pokemon && active)
    {
        //Sprite sprite = pokemon->GetFrontSprite();
        //DrawTexture(sprite.texture, currentPosition.x, currentPosition.y, WHITE);
    }
}
