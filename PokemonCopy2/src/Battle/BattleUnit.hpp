#ifndef BATTLEUNIT_HPP
#define BATTLEUNIT_HPP

#include "raylib.h"
#include "src/core/pokemonCore/Pokemon.hpp"
#include "BattleHud.hpp"
#include "src/components/AnimationComponent.hpp"
#include "src/components/Sprite.hpp"

class BattleUnit
{
private:
    Pokemon* pokemon;
    AnimationComponent* animationComponent;
    BattleHud hud;
    bool isPlayer;
    bool active;

    Rectangle rect;

    Vector2 startPosition;
    Vector2 battlePosition;
    Vector2 currentPosition;

public:
    BattleUnit();
    ~BattleUnit();

    void SetUp(Pokemon* pokemon, bool isPlayer);
    void BattleStart();
    void CreateAnimationComponent(
        Texture2D& textureSheet, int frameWidth, 
        int frameHeight);
        
    void LoadAnimations();
    void SetActive(bool active) { this->active = active; }
    void Draw();

    void PerformMoveAnimation(Move& move);

    Pokemon* GetPokemon() const { return pokemon; }
    bool IsActive() const { return active; }
};

#endif