#include "BattleHud.hpp"

void BattleHud::SetData(BattleUnit &unit, Rectangle &rect)
{
    this->unit = &unit;
    this->rect = rect;
    
    nameText = unit.GetPokemon()->species->name;
    levelText = "Lv. " + std::to_string(unit.GetPokemon()->level);
    hpText = std::to_string(unit.GetPokemon()->currentHP);
    maxHpText = std::to_string(unit.GetPokemon()->stats.hp);
}

void BattleHud::Draw()
{
    if (unit && unit->IsActive())
    {
        DrawTextureRec(hudTexture, rect, {rect.x, rect.y}, WHITE);

        DrawText(nameText.c_str(), rect.x + 10, rect.y + 10, 20, BLACK);
        DrawText(levelText.c_str(), rect.x + rect.width - 80, 
            rect.y + 10, 20, BLACK);
        DrawText((hpText + "/" + maxHpText).c_str(), rect.x + 10, 
            rect.y + 40, 20, BLACK);
    }
}