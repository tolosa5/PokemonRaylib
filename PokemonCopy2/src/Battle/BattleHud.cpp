#include "BattleHud.hpp"

void BattleHud::SetData(BattleUnit &unit, Rectangle &hud)
{
    this->unit = &unit;
    this->hud = hud;

    nameText = unit.GetPokemon()->species->name;
    levelText = "Lv. " + std::to_string(unit.GetPokemon()->level);
    hpText = std::to_string(unit.GetPokemon()->currentHP);
    maxHpText = std::to_string(unit.GetPokemon()->stats.hp);

    DrawText(nameText.c_str(), hud.x + 10, hud.y + 10, 20, BLACK);
    DrawText(levelText.c_str(), hud.x + hud.width - 80, hud.y + 10, 20, BLACK);
    DrawText((hpText + "/" + maxHpText).c_str(), hud.x + 10, hud.y + 40, 20, BLACK);
}