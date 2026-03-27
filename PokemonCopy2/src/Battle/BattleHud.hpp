#ifndef BATTLE_HUD_HPP
#define BATTLE_HUD_HPP

#include "BattleUnit.hpp"
#include "raylib.h"

class BattleHud
{
public:
    BattleUnit* unit;
    Rectangle rect;

    Texture2D hudTexture;

    std::string nameText;
    std::string levelText;
    std::string hpText;
    std::string maxHpText;

    void SetData(BattleUnit& unit, Rectangle& hud);
    void Draw();
};

#endif