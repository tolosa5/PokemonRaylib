#include "BattleUnit.hpp"

void BattleUnit::CreateAnimationComponent(Texture2D& textureSheet, 
    int frameWidth, int frameHeight)
{
    animationComponent = new AnimationComponent(textureSheet, frameWidth, frameHeight);
}

BattleUnit::BattleUnit() : pokemon(nullptr), isPlayer(false), active(true)
{
    CreateAnimationComponent(pokemon->species->spriteSheet, 64, 64);
    LoadAnimations();
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
    animationComponent->Play("ENTER_BATTLE");
}

void BattleUnit::LoadAnimations()
{
    animationComponent->AddAnimation("ENTER_BATTLE", 0, 4, 0.5f);
}

void BattleUnit::Draw()
{
    if (pokemon && active)
    {
        DrawTexture(pokemon->species->frontSprite, 
            currentPosition.x, currentPosition.y, WHITE);

        hud.Draw();
    }
}
